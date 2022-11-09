#ifndef _SOLUTIONALGORITHM_H
#define _SOLUTIONALGORITHM_H

#include "_Algorithm.h"
#include "_Solution.h"

template <class R, class V> class _SolutionAlgorithm : public _Algorithm {
public:
    _SolutionAlgorithm():_Algorithm() {}
    _SolutionAlgorithm(int seed):_Algorithm(seed) {}
    virtual ~_SolutionAlgorithm() {}    
    virtual _Solution<R, V>* solve(_Solution<R,V>* solution) = 0;
};

#endif /* _SOLUTIONALGORITHM_H */

