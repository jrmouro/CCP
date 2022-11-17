#ifndef _BUILDER_SOLUTION_H
#define _BUILDER_SOLUTION_H

#include "_Instance_Algorithm.h"

template <class V> class _Builder_Solution : public _Instance_Algorithm<V> {
public:
    _Builder_Solution() : _Instance_Algorithm<V>() { }
    _Builder_Solution(unsigned seed) : _Instance_Algorithm<V>(seed) { }
    _Builder_Solution(const _Builder_Solution<V>& other) : _Instance_Algorithm<V>(other) { }
    virtual ~_Builder_Solution() {}
};

#endif /* _BUILDER_SOLUTION_H */

