#ifndef _SOLUTIONS_ALGORITHM_H
#define _SOLUTIONS_ALGORITHM_H

#include <vector>
#include "_Solution_Algorithm.h"
#include "_Solution.h"

template <class V> class _Solutions_Algorithm : public _Solution_Algorithm<V> {
public:
    _Solutions_Algorithm() : _Solution_Algorithm<V>() { }
    virtual ~_Solutions_Algorithm() {}
    virtual std::vector<_Solution<V>*>* solvev(const _Solution<V>& solution) = 0;
};

#endif /* _SOLUTIONS_ALGORITHM_H */

