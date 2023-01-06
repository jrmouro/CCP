#ifndef _LOCAL_SEARCH_H
#define _LOCAL_SEARCH_H

#include <vector>
#include <iostream>
#include "_Solution_Algorithm.h"
#include "_Solution.h"
#include "_Solution_Comparator.h"
#include "_Neighborhood_Algorithm.h"
#include "_Selection_Algorithm.h"

template <class V> class _Local_Search : public _Solution_Algorithm<V> {
public:

    _Local_Search(
            _Neighborhood_Algorithm<V>& neighborhood,
            const _Solution_Comparator<V>& solutionComparator,
            const _Selection_Algorithm<V>& selectionAlgorithm) :
                _Solution_Algorithm<V>(),
                neighborhoodAlgorithm(neighborhood),
                solutionComparator(solutionComparator),
                selectionAlgorithm(selectionAlgorithm){}
                
    _Local_Search(const _Local_Search<V>& other) :
            neighborhoodAlgorithm(other.neighborhoodAlgorithm), 
            solutionComparator(other.solutionComparator),
            selectionAlgorithm(other.selectionAlgorithm){}


    virtual ~_Local_Search() { }
    
    virtual _Local_Search* clone(){
        return new _Local_Search(*this);
    }
    
    virtual _Solution<V>* solve(const _Solution<V>& solution) {
        
        _Solution<V>* ret = solution.clone();             
                            
        auto neighborhood = this->neighborhoodAlgorithm.solvev(*ret);

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
                    

        return ret;

    }
    
    virtual void reset(){}

protected:
    _Neighborhood_Algorithm<V>& neighborhoodAlgorithm;
    const _Solution_Comparator<V>& solutionComparator;
    const _Selection_Algorithm<V>& selectionAlgorithm;
};

#endif /* _LOCAL_SEARCH_H */

