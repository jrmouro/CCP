#ifndef CCLOCALSEARCH_H
#define CCLOCALSEARCH_H

#include "_LocalSearch.h"
#include "CCSolutionComparator.h"
#include "CCNeighborhood.h"

class CCLocalSearch : public _LocalSearch<int*, int> {
public:

    CCLocalSearch(
        CCNeighborhood* neighborhood,
        CCSolutionComparator* solutionComparator):_LocalSearch<int*, int>(
        (_NeighborhoodAlgorithm<int*,int>*)neighborhood, 
        (_SolutionComparator<int*,int>*)solutionComparator) {}

    virtual ~CCLocalSearch() { }


};

#endif /* CCLOCALSEARCH_H */

