#ifndef _LOCAL_SEARCH_H
#define _LOCAL_SEARCH_H

#include <vector>
#include "_Solution_Algorithm.h"
#include "_Solution.h"
#include "_Solution_Comparator.h"
#include "_Neighborhood_Algorithm.h"

template <class V> class _Local_Search : public _Solution_Algorithm<V> {
public:

    _Local_Search(
            const _Neighborhood_Algorithm<V>& neighborhood,
            const _Solution_Comparator<V>& solutionComparator) :
                _Solution_Algorithm<V>(),
                neighborhoodAlgorithm(neighborhood),
                solutionComparator(solutionComparator) {}
                
    _Local_Search(const _Local_Search<V>& other) :
            neighborhoodAlgorithm(other.neighborhoodAlgorithm), 
            solutionComparator(other.solutionComparator) {}


    virtual ~_Local_Search() { }
    
    virtual _Local_Search* clone(){
        return new _Local_Search(*this);
    }

    virtual _Solution<V>* solve(const _Solution<V>& solution) const {
        
        _Solution<V>* ret = solution.clone();
        
        bool flag = true;
        
        while(flag){
            
            auto neighborhood = this->neighborhoodAlgorithm.solvev(*ret);

            flag = false;
            
            for (auto neighbor : *neighborhood) {

                if (this->solutionComparator(*neighbor, *ret)) {
                    
                    delete ret;
                                                    
                    ret = neighbor;
                    
                    flag = true;

                } else {
                    
                    delete neighbor;
                    
                }

            }
            
            delete neighborhood;
                    
        }

        return ret;

    }

protected:
    const _Neighborhood_Algorithm<V>& neighborhoodAlgorithm;
    const _Solution_Comparator<V>& solutionComparator;

};

#endif /* _LOCAL_SEARCH_H */

