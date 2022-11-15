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

class CCGrasp : public _Grasp<int*,float> {
public:
    CCGrasp( CCBuilderSolution* builderSolution, 
            CCStopCondition* stopCondition,
            CCSolutionDisturber* solutionDisturber,
            CCLocalSearch* localSearch,
            CCSolutionComparator* solutionComparator):_Grasp<int*,float>(
                        (_BuilderSolution<int*,float>*)builderSolution,
                        (_StopCondition<int*,float>*)stopCondition,
                        (_SolutionDisturber<int*,float>*)solutionDisturber,
                        (_LocalSearch<int*,float>*)localSearch,
                        (_SolutionComparator<int*,float>*)solutionComparator){}
                            
    virtual ~CCGrasp(){}
    
};

#endif /* CCGRASP_H */

