#ifndef CCGRASP_MPI_H
#define CCGRASP_MPI_H

#include <mpi.h>
#include <iostream>
#include "_Grasp.h"
#include "CCSolutionComparator.h"
#include "CCSolutionDisturber.h"
#include "CCStopCondition.h"
#include "CCBuilderSolution.h"
#include "CCLocalSearch_mpi.h"

class  CCGrasp_mpi : public _Grasp<float> {
public:

    CCGrasp_mpi(
            int node,
            CCStopCondition& stopCondition,
            CCSolutionDisturber& solutionDisturber,
            CCLocalSearch_mpi& localSearch,
            const CCSolutionComparator& solutionComparator) :
                node(node), comm_sz(comm_sz),
                _Grasp<float>(
                    (_Stop_Condition<float>&)stopCondition,
                    (_Solution_Disturber<float>&)solutionDisturber,
                    (_Local_Search<float>&)localSearch,
                    (const _Solution_Comparator<float>&)solutionComparator) { }

    
    virtual ~CCGrasp_mpi() {}

    virtual _Solution<float>* solve(const _Solution<float>& solution) {

        this->stopCondition.reset(); 
        
        _Solution<float>* ret = nullptr;

        if(node == 0){
            ret = solution.clone();
        }

        bool flag = 1;

        while (flag) {

            _Solution<float>* aux = nullptr;

            if(node == 0){

                aux = this->solutionDisturber.solve(*ret);

            }

            
            auto solutionAux = this->localSearch.solve(*aux);

            // std::cout << node << " - ls aux: " << solutionAux->GetEvaluation() << std::endl;

            if(node == 0){

                if (this->solutionComparator(*solutionAux, *ret)) {

                    delete ret;

                    ret = solutionAux;

                } else {

                    delete solutionAux;

                }

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

    int node, comm_sz;

};

#endif /* CCGRASP_H */

