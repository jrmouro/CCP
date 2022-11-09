#ifndef _LOCALSEARCH_H
#define _LOCALSEARCH_H

#include <vector>
#include "_Algorithm.h"
#include "_Solution.h"
#include "_SolutionComparator.h"

template <class R, class V> class _LocalSearch : public _SolutionAlgorithm<R, V> {
public:

    _LocalSearch(const _SolutionComparator<_Solution<R, V>>& solutionComparator) :
                solutionComparator(solutionComparator) {}

    virtual ~_LocalSearch() { }

    virtual _Solution<R, V> solve(const _Solution& solution) {

        auto neighborhood = this->neighborhood();

        _Solution<R, V> ret = solution;
        
        bool flag = false;

        for (auto neighbor : neighborhood) {

            if (this->solutionComparator(neighbor, ret)) {

                ret = neighbor;
                
                flag = true;

            }

        }

        if (flag) {

            return this->solve(ret);

        }

        return ret;

    }

protected:
    virtual std::vector<_Solution<R, V>> neighborhood() = 0;
    const _SolutionComparator<_Solution<R, V>>& solutionComparator;

};

#endif /* _LOCALSEARCH_H */

