#ifndef _SOLUTION_H
#define _SOLUTION_H

#include "_Evaluable.h"

template <class V> class _Solution : public _Evaluable<V> {
public:
    _Solution():_Evaluable<V>(){}
    _Solution(const V& value):_Evaluable<V>(value){}
    _Solution(const _Solution<V>& orig):_Evaluable<V>(orig){}
    virtual ~_Solution() {}
    virtual _Solution<V>* clone() const = 0;
};

#endif /* _SOLUTION_H */

