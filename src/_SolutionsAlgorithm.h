#ifndef _SOLUTIONSALGORITHM_H
#define _SOLUTIONSALGORITHM_H

#include <vector>
#include "_Solution.h"

template <class R, class V> class _SolutionsAlgorithm : public _Algorithm {
public:
    _SolutionsAlgorithm():_Algorithm() {}
    _SolutionsAlgorithm(int seed):_Algorithm(seed) {}
    virtual ~_SolutionsAlgorithm() {}
    virtual std::vector<_Solution<R, V>*>* solve(_Solution<R,V>* solution) = 0;
};

#endif /* _SOLUTIONSALGORITHM_H */

