#ifndef _SOLUTIONSALGORITHM_H
#define _SOLUTIONSALGORITHM_H

template <class R, class V> class _SolutionsAlgorithm : public _Algorithm {
public:
    virtual ~_SolutionsAlgorithm() {}
    virtual std::vector<_Solution<R, V>> solve(const _Solution& solution) = 0;
};

#endif /* _SOLUTIONSALGORITHM_H */

