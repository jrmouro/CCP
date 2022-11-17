#ifndef _INSTACE_ALGORITHM_H
#define _INSTACE_ALGORITHM_H

#include "_Estochastic_Algorithm.h"
#include "_Instance.h"
#include "_Solution.h"

template <class V> class _Instance_Algorithm : public _Estochastic_Algorithm {
public:    
    _Instance_Algorithm() : _Estochastic_Algorithm() { } 
    _Instance_Algorithm(unsigned seed) : _Estochastic_Algorithm(seed) { }    
    _Instance_Algorithm(const _Instance_Algorithm<V>& other) : _Estochastic_Algorithm(other) {}
    virtual ~_Instance_Algorithm(){}
    virtual _Solution<V>* solve(const _Instance& instance) = 0;
};

#endif /* _INSTACE_ALGORITHM_H */

