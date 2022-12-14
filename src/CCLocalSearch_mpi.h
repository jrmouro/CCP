#ifndef CCLOCALSEARCH_MPI_H
#define CCLOCALSEARCH_MPI_H

#include "_Local_Search.h"
#include "CCSolutionComparator.h"
#include "CCNeighborhood_mpi.h"

class CCLocalSearch_mpi : public CCLocalSearch {
public:

    CCLocalSearch_mpi(
        int node,
        CCNeighborhood_mpi& neighborhood,
        const CCSolutionComparator& solutionComparator,
        const _Selection_Algorithm<float>& selectionAlgorithm):
            CCLocalSearch(
                neighborhood, 
                solutionComparator,
                selectionAlgorithm),                
            node(node){}

    virtual ~CCLocalSearch_mpi() { }

    virtual _Solution<float>* solve(const _Solution<float>& solution) {

        _Solution<float>* ret = nullptr;

        if(this->node == 0){

            ret = solution.clone();

        }
                                           
        auto neighborhood = this->neighborhoodAlgorithm.solvev(*ret);

        if(this->node == 0){

            auto neighbor = this->selectionAlgorithm.solve(*neighborhood);

            if(neighbor != nullptr){

                if (this->solutionComparator(*neighbor, *ret)) {

                    delete ret;

                    ret = neighbor;               

                } else {

                    delete neighbor;

                } 

            }

            for (auto neighbor : *neighborhood) {

                delete neighbor;

            }

            delete neighborhood;

        }      
                    
        return ret;

    }

    private:

        int node


};

#endif /* CCLOCALSEARCH_MPI_H */

