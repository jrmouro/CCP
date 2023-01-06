#ifndef CCNEIGHBORHOOD_MPI_H
#define CCNEIGHBORHOOD_MPI_H

#include <vector>
#include <iostream>
#include "_Solution.h"
#include "CCSolution.h"
#include "CCNeighborhood.h"

class CCNeighborhood_mpi : public CCNeighborhood {
public:

    CCNeighborhood_mpi(
            int node, int comm_sz,
            const CCInstance& instance,
            const _Solution_Comparator<float>& solutionComparator) : 
                CCNeighborhood(solutionComparator),                 
                node(node), comm_sz(comm_sz),
                instance(instance) {}

    CCNeighborhood_mpi(
            const CCNeighborhood_mpi& other) : 
                CCNeighborhood(other), 
                node(other.node), comm_sz(other.comm_sz), instance(other.instance){}

    virtual ~CCNeighborhood_mpi() { }

    virtual std::vector<_Solution<float>*>* solvev(const _Solution<float>& solution) {

        std::vector<_Solution<float>*>* ret = nullptr;

        if(this->node == 0){

            ret = new std::vector<_Solution<float>*>();

        }

        auto solutionAux = this->solve(solution);

        if(this->node == 0){

            ret->push_back(solutionAux); 

        }

        return ret;

    }

    virtual _Solution<float>* solve(const _Solution<float>& solution) {

        _Solution<float>* ret;//, *sol;
        int nClusters = instance.GetNClusters();
        int size = instance.GetSize();
        int rep_size = instance.GetSize() * instance.GetNClusters();
        
        if(this->node == 0){
           
            ret = solution.clone();
            //sol = solution.clone();
            // std::cout << "node: " << node << ": " << ret->GetEvaluation() << std::endl;
            auto sRep = ((CCSolution*) ret)->GetRepresentation();
            MPI_Bcast(sRep, rep_size, MPI_INT, 0,  MPI_COMM_WORLD);
            delete sRep;
        } else {
            auto sRep = new int[rep_size];
            MPI_Bcast(sRep, rep_size, MPI_INT, 0,  MPI_COMM_WORLD);
            ret = new CCSolution(instance, sRep);
            //sol = ret->clone();
            // std::cout << "node: " << node << ": " << ret->GetEvaluation() << std::endl;
            delete sRep;
        }

        int _size = size / this->comm_sz;

        int aux = this->node * _size + _size;

        for (int n = this->node * _size; n < aux; n++) {

            for (int i = 0; i < nClusters - 1; i++) {

                for (int j = 0; j < nClusters; j++) {

                    auto s = (CCSolution*) ret->clone();

                    float aux = s->SwapNodo(n, i, j);
                                            
                    if (this->solutionComparator(*s, *ret)) {

                        delete ret;
                        ret = s;

                    } else {

                        delete s;

                    }                        
                    
                }
            }
        }

        if (node == 0) {

            for (int i = 1; i < comm_sz; i++) {

                auto sRep = new int[rep_size];
                MPI_Recv(sRep, rep_size, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                auto solutionAux = new CCSolution(instance, sRep);
                delete sRep;

                if (this->solutionComparator(*solutionAux, *ret)) {

                    delete ret;

                    ret = solutionAux;

                    // std::cout << i << "+t: " << ret->GetEvaluation() << std::endl;

                } else {

                    // std::cout << i << "-t: " << solutionAux2->GetEvaluation() << std::endl;

                    delete solutionAux;

                }

            }

        } else {

            auto sRep = ((CCSolution*)ret)->GetRepresentation();
            MPI_Send(sRep, rep_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
            delete sRep;
            delete ret;
            ret = nullptr;

        }

        // delete sol;    

        //std::cout << ret->GetEvaluation() << std::endl;
        
        return ret;

    }

    virtual CCNeighborhood_mpi* clone() {
        return new CCNeighborhood_mpi(*this);
    }

private:
    const CCInstance& instance;
    int node, comm_sz;

};

#endif /* CCNEIGHBORHOOD_MPI_H */