#ifndef _SOLUTION_ALGORITHM_H
#define _SOLUTION_ALGORITHM_H

#include "_Algorithm.h"
#include "_Solution.h"

template <class V> class _Solution_Algorithm : public _Algorithm {
public:
    _Solution_Algorithm():_Algorithm() {}
    virtual ~_Solution_Algorithm() {}    
    virtual _Solution<V>* solve(const _Solution<V>& solution) const = 0;
};

#endif /* _SOLUTION_ALGORITHM_H */

