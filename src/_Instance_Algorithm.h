#ifndef _INSTACE_ALGORITHM_H
#define _INSTACE_ALGORITHM_H

#include "_Algorithm.h"
#include "_Instance.h"
#include "_Solution.h"

template <class V> class _Instance_Algorithm : public _Algorithm {
public:    
    _Instance_Algorithm() : _Algorithm() { }    
    _Instance_Algorithm(const _Instance_Algorithm<V>& other) : _Algorithm(other) {}
    virtual ~_Instance_Algorithm(){}
    virtual _Solution<V>* solve(const _Instance& instance) = 0;
};

#endif /* _INSTACE_ALGORITHM_H */

