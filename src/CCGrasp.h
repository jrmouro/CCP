#ifndef CCGRASP_H
#define CCGRASP_H

#include "_Grasp.h"
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

class CCGrasp : public _Grasp<float> {
public:
    CCGrasp( 
            unsigned seed,
            CCBuilderSolution& builderSolution, 
            CCStopCondition& stopCondition,
            CCSolutionDisturber& solutionDisturber,
            const CCLocalSearch& localSearch,
            const CCSolutionComparator& solutionComparator):
                    _Grasp<float>(
                        seed,
                        (_Builder_Solution<float>&)builderSolution,
                        (_Stop_Condition<float>&)stopCondition,
                        (_Solution_Disturber<float>&)solutionDisturber,
                        (const _Local_Search<float>&)localSearch,
                        (const _Solution_Comparator<float>&)solutionComparator){}
    
    CCGrasp( 
            CCBuilderSolution& builderSolution, 
            CCStopCondition& stopCondition,
            CCSolutionDisturber& solutionDisturber,
            const CCLocalSearch& localSearch,
            const CCSolutionComparator& solutionComparator):
                    _Grasp<float>(
                        (_Builder_Solution<float>&)builderSolution,
                        (_Stop_Condition<float>&)stopCondition,
                        (_Solution_Disturber<float>&)solutionDisturber,
                        (const _Local_Search<float>&)localSearch,
                        (const _Solution_Comparator<float>&)solutionComparator){}
                            
    virtual ~CCGrasp(){}
    
};

#endif /* CCGRASP_H */

