#ifndef CCGRASP_H
#define CCGRASP_H

#include "_Grasp.h"
#include "CCSolutionComparator.h"
#include "CCSolutionDisturber.h"
#include "CCStopCondition.h"
#include "CCBuilderSolution.h"
#include "CCLocalSearch.h"
#include "_BuilderSolution.h"
#include "_LocalSearch.h"
#include "_SolutionComparator.h"
#include "_SolutionDisturber.h"
#include "_StopCondition.h"

class CCGrasp : public _Grasp<int*,int> {
public:
    CCGrasp( CCBuilderSolution* builderSolution, 
            CCStopCondition* stopCondition,
            CCSolutionDisturber* solutionDisturber,
            CCLocalSearch* localSearch,
            CCSolutionComparator* solutionComparator):_Grasp<int*,int>(
                        (_BuilderSolution<int*,int>*)builderSolution,
                        (_StopCondition<int*,int>*)stopCondition,
                        (_SolutionDisturber<int*,int>*)solutionDisturber,
                        (_LocalSearch<int*,int>*)localSearch,
                        (_SolutionComparator<int*,int>*)solutionComparator){}
                            
    virtual ~CCGrasp(){}
    
};

#endif /* CCGRASP_H */

