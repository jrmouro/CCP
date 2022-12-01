#ifndef _SELECTION_ALGORITHM_H
#define _SELECTION_ALGORITHM_H

#include <vector>
#include "_Algorithm.h"

template <class V> class _Selection_Algorithm : public _Algorithm {
public:

    _Selection_Algorithm() : _Algorithm(){ }

    _Selection_Algorithm(const _Selection_Algorithm<V>& other) : _Algorithm(other){ }

    virtual ~_Selection_Algorithm() { }

    virtual _Solution<V>* solve(const std::vector<_Solution<V>*>& solutions) const = 0;
    
    virtual void reset(){}
    
};

#endif /* _SELECT_ALGORITHM_H */

