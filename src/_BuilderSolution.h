#ifndef _BUILDERSOLUTION_H
#define _BUILDERSOLUTION_H

#include "_InstanceAlgorithm.h"

template <class R, class V> class _BuilderSolution : public _InstanceAlgorithm<R,V> {
public:
    _BuilderSolution():_InstanceAlgorithm<R,V>() {}
    _BuilderSolution(int seed):_InstanceAlgorithm<R,V>(seed) {}
    virtual ~_BuilderSolution() {}
};

#endif /* _BUILDERSOLUTION_H */

