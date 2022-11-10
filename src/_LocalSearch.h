#ifndef _LOCALSEARCH_H
#define _LOCALSEARCH_H

#include <vector>
#include "_SolutionAlgorithm.h"
#include "_Solution.h"
#include "_SolutionComparator.h"
#include "_NeighborhoodAlgorithm.h"

template <class R, class V> class _LocalSearch : public _SolutionAlgorithm<R, V> {
public:

    _LocalSearch(
            _NeighborhoodAlgorithm<R,V>* neighborhood,
            _SolutionComparator<R, V>* solutionComparator) :
                neighborhoodAlgorithm(neighborhood),
                solutionComparator(solutionComparator) {}

    virtual ~_LocalSearch() { }

    virtual _Solution<R, V>* solve(_Solution<R, V>* solution) {
        
        _Solution<R, V>* ret = solution;
        
        bool flag = true;
        
        while(flag){
            
            auto neighborhood = this->neighborhoodAlgorithm->solve(ret);

            flag = false;
            
            for (auto neighbor : *neighborhood) {

                if ((*this->solutionComparator)(*neighbor, *ret)) {

                    if(ret != solution) delete ret;

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
    _NeighborhoodAlgorithm<R,V>* neighborhoodAlgorithm;
    _SolutionComparator<R,V>* solutionComparator;

};

#endif /* _LOCALSEARCH_H */

