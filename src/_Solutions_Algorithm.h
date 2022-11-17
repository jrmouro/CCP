#ifndef _SOLUTIONS_ALGORITHM_H
#define _SOLUTIONS_ALGORITHM_H

#include <vector>
#include "_Algorithm.h"
#include "_Solution.h"

template <class V> class _Solutions_Algorithm : public _Algorithm {
public:
    virtual ~_Solutions_Algorithm() {}
    virtual std::vector<_Solution<V>*>* solvev(const _Solution<V>& solution) const = 0;
};

#endif /* _SOLUTIONS_ALGORITHM_H */

