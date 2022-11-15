#ifndef CCGRASP_OMP_H
#define CCGRASP_OMP_H

#include "_Grasp_omp.h"
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

class CCGrasp_omp : public _Grasp_omp<int*,float> {
public:
    CCGrasp_omp( 
            unsigned numThreads,
            CCBuilderSolution* builderSolution, 
            CCStopCondition* stopCondition,
            CCSolutionDisturber* solutionDisturber,
            CCLocalSearch* localSearch,
            CCSolutionComparator* solutionComparator):_Grasp_omp<int*,float>(
                        numThreads,
                        (_BuilderSolution<int*,float>*)builderSolution,
                        (_StopCondition<int*,float>*)stopCondition,
                        (_SolutionDisturber<int*,float>*)solutionDisturber,
                        (_LocalSearch<int*,float>*)localSearch,
                        (_SolutionComparator<int*,float>*)solutionComparator){}
                            
    virtual ~CCGrasp_omp(){}
    
};

#endif /* CCGRASP_OMP_H */

