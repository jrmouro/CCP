#ifndef _STOP_CONDITION_H
#define _STOP_CONDITION_H

#include "_Solution.h"
#include "_Clonable.h"

template <class V> class _Stop_Condition: public _Clonable {
public:
    virtual ~_Stop_Condition(){}
    virtual bool stop(const _Solution<V>& solution) = 0;
    virtual void reset() = 0;
    virtual _Stop_Condition* clone() = 0;
};

#endif /* _STOP_CONDITION_H */

