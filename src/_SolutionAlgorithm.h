#ifndef _SOLUTIONALGORITHM_H
#define _SOLUTIONALGORITHM_H

template <class R, class V> class _SolutionAlgorithm : public _Algorithm {
public:
    virtual ~_SolutionAlgorithm() {}
    virtual _Solution<R, V> solve(const _Solution& solution) = 0;
};

#endif /* _SOLUTIONALGORITHM_H */

