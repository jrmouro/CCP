#ifndef CCGRASP_OMP_H
#define CCGRASP_OMP_H

#include "_Grasp_omp.h"
#include "CCSolutionComparator.h"
#include "CCSolutionDisturber.h"
#include "CCStopCondition.h"
#include "CCBuilderSolution.h"
#include "CCLocalSearch.h"
#include "_Builder_Solution.h"
#include "_Local_Search.h"
#include "_Solution_Comparator.h"
#include "_Solution_Disturber.h"
#include "_Stop_Condition.h"

class CCGrasp_omp : public _Grasp_omp<float> {
public:
    CCGrasp_omp( 
            unsigned numThreads,
            CCStopCondition& stopCondition,
            CCSolutionDisturber& solutionDisturber,
            const CCLocalSearch& localSearch,
            const CCSolutionComparator& solutionComparator):
                    _Grasp_omp<float>(
                        numThreads,
                        (_Stop_Condition<float>&)stopCondition,
                        (_Solution_Disturber<float>&)solutionDisturber,
                        (_Local_Search<float>&)localSearch,
                        (const _Solution_Comparator<float>&)solutionComparator){}
    
    
    
    virtual ~CCGrasp_omp(){}
    
};

#endif /* CCGRASP_OMP_H */

