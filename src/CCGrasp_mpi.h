#ifndef CCGRASP_MPI_H
#define CCGRASP_MPI_H

#include <mpi.h>
#include <iostream>
#include "_Grasp.h"
#include "CCSolutionComparator.h"
#include "CCSolutionDisturber.h"
#include "CCStopCondition.h"
#include "CCBuilderSolution.h"
#include "CCLocalSearch.h"
#include "_Builder_Solution.h"
#include "_Local_Search.h"
#include "_Solution_Comparator.h"
#include "_Solution_Disturber.h"
#include "_Stop_Condition.h"

class CCGrasp_mpi : public _Grasp<float> {
public:

    CCGrasp_mpi(
            const CCInstance& instance,
            int node, int comm_sz,
            CCStopCondition& stopCondition,
            CCSolutionDisturber& solutionDisturber,
            CCLocalSearch& localSearch,
            const CCSolutionComparator& solutionComparator) :
                instance(instance),node(node), comm_sz(comm_sz),
                _Grasp<float>(
                    (_Stop_Condition<float>&)stopCondition,
                    (_Solution_Disturber<float>&)solutionDisturber,
                    (_Local_Search<float>&)localSearch,
                    (const _Solution_Comparator<float>&)solutionComparator) { }

    
    virtual ~CCGrasp_mpi() {}

    virtual _Solution<float>* solve(const _Solution<float>& solution) {

        this->stopCondition.reset(); 

        int rep_size = instance.GetSize() * instance.GetNClusters();
        this->solutionDisturber.SetAmount(comm_sz - 1);

        _Solution<float>* ret = nullptr;

        if(node == 0){
            ret = solution.clone();
        }

        bool flag = 1;

        while (flag) {

            if (node == 0) {

                auto aux = this->solutionDisturber.solvev(*ret);

                int count = 1;
                for (auto elem : *aux) {
                    auto sRep = ((CCSolution*) elem)->GetRepresentation();
                    MPI_Send(sRep, rep_size, MPI_INT, count, 0, MPI_COMM_WORLD);
                    delete elem;
                    count++;
                }

                delete aux;

                // std::cout << "b0: " << ret->GetEvaluation() << std::endl;

            } else {

                auto sRep = new int[rep_size];
                MPI_Recv(sRep, rep_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                ret = new CCSolution(instance, sRep);
                delete sRep;

            }

            // std::cout << node << " - ret: " << ret->GetEvaluation() << std::endl;

            auto solutionAux = this->localSearch.solve(*ret);

            // std::cout << node << " - ls aux: " << solutionAux->GetEvaluation() << std::endl;

            if (this->solutionComparator(*solutionAux, *ret)) {

                delete ret;

                ret = solutionAux;

                // if(node == 0)
                // std::cout << "+s0: " << ret->GetEvaluation() << std::endl;

            } else {

                // if(node == 0)
                // std::cout << "-s0: " << solutionAux->GetEvaluation() << std::endl;


                delete solutionAux;

            }

            if (node == 0) {

                for (int i = 1; i < comm_sz; i++) {

                    auto sRep = new int[rep_size];
                    MPI_Recv(sRep, rep_size, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    auto solutionAux2 = new CCSolution(instance, sRep);
                    delete sRep;

                    if (this->solutionComparator(*solutionAux2, *ret)) {

                        delete ret;

                        ret = solutionAux2;

                        // std::cout << i << "+t: " << ret->GetEvaluation() << std::endl;

                    } else {

                        // std::cout << i << "-t: " << solutionAux2->GetEvaluation() << std::endl;

                        delete solutionAux2;

                    }

                }

            } else {

                auto sRep = ((CCSolution*)ret)->GetRepresentation();
                MPI_Send(sRep, rep_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
                delete sRep;

            }

            if(node == 0){

                if (this->stopCondition.stop(*ret)) {

                    flag = 0;

                }

                MPI_Bcast(&flag, 1, MPI_INT, 0,  MPI_COMM_WORLD);


            } else {

                 MPI_Bcast(&flag, 1, MPI_INT, 0,  MPI_COMM_WORLD);

            }
            

        }

        // std::cout << node << "++: " << ret->GetEvaluation() << std::endl;


        return ret;

    }

    virtual CCGrasp_mpi* clone() {
        return new CCGrasp_mpi(*this);
    }

private:
    const CCInstance& instance;
    int node, comm_sz;

};

#endif /* CCGRASP_H */

