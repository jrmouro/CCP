#ifndef _ESTOCHASTIC_SOLUTION_ALGORITHM_H
#define _ESTOCHASTIC_SOLUTION_ALGORITHM_H

#include "_Estochastic_Algorithm.h"
#include "_Solution.h"

template <class V> class _Estochastic_Solution_Algorithm : public _Estochastic_Algorithm {
public:
    _Estochastic_Solution_Algorithm():_Estochastic_Algorithm() {}
    _Estochastic_Solution_Algorithm(int seed):_Estochastic_Algorithm(seed) {}
    _Estochastic_Solution_Algorithm(const _Estochastic_Solution_Algorithm<V>& other) :
        _Estochastic_Algorithm(other) {}
    virtual ~_Estochastic_Solution_Algorithm() {}    
    virtual _Solution<V>* solve(const _Solution<V>& solution) = 0;
};

#endif /* _ESTOCHASTIC_SOLUTIONALGORITHM_H */

