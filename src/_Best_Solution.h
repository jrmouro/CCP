#ifndef _BEST_SOLUTION_H
#define _BEST_SOLUTION_H

#include <vector>
#include "_Selection_Algorithm.h"
#include "_Solution.h"
#include "_Solution_Comparator.h"

template <class V> class _Best_Solution : public _Selection_Algorithm<V> {
public:

    _Best_Solution(const _Solution_Comparator<V>& solutionComparator) :
            _Selection_Algorithm<V>(),
            solutionComparator(solutionComparator) { }

    _Best_Solution(const _Best_Solution<V>& other) :
            _Selection_Algorithm<V>(other),
            solutionComparator(other.solutionComparator) { }

    virtual ~_Best_Solution() { }

    virtual _Best_Solution* clone() {
        return new _Best_Solution(*this);
    }

    virtual _Solution<V>* solve(const std::vector<_Solution<V>*>& solutions) const {

        _Solution<V>* ret = nullptr;

        for (auto solution : solutions) {

            if (ret == nullptr){
                
                ret = solution;
                
            } else if(this->solutionComparator(*solution, *ret)) {
                
                ret = solution;
                
            }

        }

        if(ret != nullptr)

            return ret->clone();
        
        return ret;

    }

protected:
    
    const _Solution_Comparator<V>& solutionComparator;

};

#endif /* _BEST_SOLUTION_H */

