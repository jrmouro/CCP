#ifndef _SOLUTION_H
#define _SOLUTION_H

#include <vector>

template <class R, class V> class _Solution : public _Evaluable<V> {
public:
    _Solution():_Evaluable(){}
    _Solution(const V& value):_Evaluable(value){}
    _Solution(const _Solution<R,V>& orig):_Evaluable(orig){}
    virtual ~_Solution() {}
    virtual R representation() const = 0;
    virtual _Solution<R, V>* build(const R& representation) const = 0;
};

#endif /* _SOLUTION_H */

