#ifndef CCLOCALSEARCH_H
#define CCLOCALSEARCH_H

#include "_Local_Search.h"
#include "CCSolutionComparator.h"
#include "CCNeighborhood.h"

class CCLocalSearch : public _Local_Search<float> {
public:

    CCLocalSearch(
        const CCNeighborhood& neighborhood,
        const CCSolutionComparator& solutionComparator):
            _Local_Search<float>(
                (const _Neighborhood_Algorithm<float>&)neighborhood, 
                (const _Solution_Comparator<float>&)solutionComparator) {}

    virtual ~CCLocalSearch() { }


};

#endif /* CCLOCALSEARCH_H */

