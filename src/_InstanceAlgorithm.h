#ifndef _INSTACEALGORITHM_H
#define _INSTACEALGORITHM_H

#include "_Algorithm.h"

template <class R, class V> class _InstanceAlgorithm : public _Algorithm {
public:
    _InstanceAlgorithm():_Algorithm() {}
    _InstanceAlgorithm(int seed):_Algorithm(seed) {}
    virtual ~_InstanceAlgorithm() {}
    virtual _Solution<R, V>* solve(_Instance* instance) = 0;
};

#endif /* _INSTACEALGORITHM_H */

