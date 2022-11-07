#ifndef _SOLUTIONCOMPARATOR_H
#define _SOLUTIONCOMPARATOR_H

template <class R, class V>  class _SolutionComparator {
public:
    virtual bool operator()(_Solution<R,V>& s1, _Solution<R,V>& s2) const = 0;
    virtual ~_SolutionComparator(){}
};

#endif /* _SOLUTIONCOMPARATOR_H */

