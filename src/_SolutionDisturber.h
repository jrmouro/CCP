#ifndef _DISTURB_H
#define _DISTURB_H

#include "_SolutionAlgorithm.h"

template <class R, class V> class _SolutionDisturber: public _SolutionAlgorithm<R, V>{
public:
    _SolutionDisturber():_SolutionAlgorithm<R, V>() {}
    _SolutionDisturber(int seed):_SolutionAlgorithm<R, V>(seed) {}
    virtual ~_SolutionDisturber(){}
};

#endif /* _DISTURB_H */

