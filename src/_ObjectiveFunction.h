#ifndef _OBJECTIVEFUNCTION_H
#define _OBJECTIVEFUNCTION_H

#include "_Solution.h"

template <class R, class V> class _ObjectiveFunction {
public:
    virtual ~_ObjectiveFunction(){}
    virtual V evaluate(const _Solution<R,V> &solution) = 0;
};

#endif /* _OBJECTIVEFUNCTION_H */

