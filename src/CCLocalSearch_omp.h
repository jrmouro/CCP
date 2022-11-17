#ifndef CCLOCALSEARCH_OMP_H
#define CCLOCALSEARCH_OMP_H

#include "_Local_Search_omp.h"
#include "CCSolutionComparator.h"
#include "CCNeighborhood.h"

class CCLocalSearch_omp : public _Local_Search_omp<float> {
public:

    CCLocalSearch_omp(
        unsigned numThreads,
        const CCNeighborhood& neighborhood,
        const CCSolutionComparator& solutionComparator):
            _Local_Search_omp<float>(
                numThreads,
                (const _Neighborhood_Algorithm<float>&)neighborhood, 
                (const _Solution_Comparator<float>&)solutionComparator) {}

    virtual ~CCLocalSearch_omp() { }


};

#endif /* CCLOCALSEARCH_OMP_H */

