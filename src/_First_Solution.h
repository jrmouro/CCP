#ifndef _FIRST_SOLUTION_H
#define _FIRST_SOLUTION_H

#include <vector>
#include "_Selection_Algorithm.h"
#include "_Solution.h"
#include "_Solution_Comparator.h"

template <class V> class _First_Solution : public _Selection_Algorithm<V> {
public:

    _First_Solution(const _Solution_Comparator<V>& solutionComparator) :
            _Selection_Algorithm<V>(),
            solutionComparator(solutionComparator) {  }

    _First_Solution(const _First_Solution<V>& other) :
            _Selection_Algorithm<V>(other),
            solutionComparator(other.solutionComparator) {  }

    virtual ~_First_Solution() {
    }

    virtual _First_Solution* clone() {
        return new _First_Solution(*this);
    }

    virtual _Solution<V>* solve(const std::vector<_Solution<V>*>& solutions) const {

        _Solution<V>* ret = nullptr;

        for (auto solution : solutions) {

            if (ret == nullptr) {

                ret = solution;

            } else {

                if (this->solutionComparator(*solution, *ret)) {

                    return solution->clone();

                }

            }

        }
        
        if(ret != nullptr)

            return ret->clone();
        
        return ret;

    }

protected:

    const _Solution_Comparator<V>& solutionComparator;

};

#endif /* _FIRST_SOLUTION_H */

