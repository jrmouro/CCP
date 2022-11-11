#ifndef CCSTOPCONDITION_H
#define CCSTOPCONDITION_H

#include "_StopCondition.h"
#include "_Solution.h"

class CCStopCondition : public _StopCondition<int*,float>{
public:
    
    CCStopCondition(float literature_solution, float threshold):_threshold(threshold), _literature_solution(literature_solution){}
    
    virtual ~CCStopCondition(){}
    
    virtual bool stop(_Solution<int*,float>* solution){        
        const float evaluation = solution->GetEvaluation();
        return evaluation >= (_literature_solution * _threshold);       
    }
    
    virtual void reset(){        
        current = 0;        
    }
private:
    int nIterations, current = 0;
    float _literature_solution;
    float _threshold;
};

#endif /* CCSTOPCONDITION_H */

