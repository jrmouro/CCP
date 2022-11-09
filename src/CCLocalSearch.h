#ifndef CCLOCALSEARCH_H
#define CCLOCALSEARCH_H

#include "_LocalSearch.h"
#include "CCSolutionComparator.h"
#include "CCNeighborhood.h"

class CCLocalSearch : public _LocalSearch<int*, float> {
public:

    CCLocalSearch(
        CCNeighborhood* neighborhood,
        CCSolutionComparator* solutionComparator):_LocalSearch<int*, float>(
        (_NeighborhoodAlgorithm<int*,float>*)neighborhood, 
        (_SolutionComparator<int*,float>*)solutionComparator) {}

    virtual ~CCLocalSearch() { }


};

#endif /* CCLOCALSEARCH_H */

