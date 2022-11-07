#ifndef _INSTACEALGORITHM_H
#define _INSTACEALGORITHM_H

template <class R, class V> class _InstanceAlgorithm : public _Algorithm {
public:
    virtual ~_InstanceAlgorithm() {}
    virtual _Solution<R, V> solve(const _Instance& instance) = 0;
};

#endif /* _INSTACEALGORITHM_H */

