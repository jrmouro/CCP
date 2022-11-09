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
                neighborhood(neighborhood),
                solutionComparator(solutionComparator) {}

    virtual ~_LocalSearch() { }

    virtual _Solution<R, V>* solve(_Solution<R, V>* solution) {

        auto neighborhood = this->neighborhood->solve(solution);

        _Solution<R, V>* ret = solution;
        
        bool flag = false;

        for (auto neighbor : *neighborhood) {

            if ((*this->solutionComparator)(*neighbor, *ret)) {

                ret = neighbor;
                
                flag = true;

            } else {
                
                delete neighbor;
                
            }

        }
        
        delete neighborhood;

        if (flag) {

            return this->solve(ret);

        }

        return ret;

    }

protected:
    _NeighborhoodAlgorithm<R,V>* neighborhood;
    _SolutionComparator<R,V>* solutionComparator;

};

#endif /* _LOCALSEARCH_H */

