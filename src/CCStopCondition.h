#ifndef _STOPCONDITION_H
#define _STOPCONDITION_H

#include "_Solution.h"

template <class R, class V> class _StopCondition {
public:
    virtual ~_StopCondition();
    virtual bool stop(const _Solution<R,V>& solution) = 0;
};

#endif /* _STOPCONDITION_H */

