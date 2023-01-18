#ifndef _SOLUTION_COMPARATOR_H
#define _SOLUTION_COMPARATOR_H

#include "_Solution.h"
#include "_Clonable.h"

template <class V>  class _Solution_Comparator : public _Clonable{
public:
    virtual bool operator()(const _Solution<V>& s1, const _Solution<V>& s2) const = 0;
    virtual bool operator()(const _Solution<V>& solution, const V& value) const = 0;
    virtual ~_Solution_Comparator(){}
    virtual _Solution_Comparator* clone() = 0;

    bool compare(const _Solution<V>& s1, const _Solution<V>& s2)const{
        return this->operator()(s1, s2);
        
    }

    bool compare(const _Solution<V>& solution, const V& value)const{
        return this->operator()(solution, value);
    }

};

#endif /* _SOLUTION_COMPARATOR_H */

