#ifndef _NEIGHBORHOOD_ALGORITHM_H
#define _NEIGHBORHOOD_ALGORITHM_H

#include "_Solutions_Algorithm.h"
#include "_Clonable.h"

template <class V> class _Neighborhood_Algorithm : 
        public _Solutions_Algorithm<V>{
public:
    virtual ~_Neighborhood_Algorithm() {}
};

#endif /* _NEIGHBORHOODALGORITHM_H */

