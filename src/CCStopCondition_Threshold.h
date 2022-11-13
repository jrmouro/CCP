#ifndef CCSTOPCONDITION_THRESHOLD_H
#define CCSTOPCONDITION_THRESHOLD_H

#include "CCStopCondition.h"
#include "_Solution.h"

class CCStopCondition_Threshold : public CCStopCondition{
public:
    
    CCStopCondition_Threshold(float threshold, int nIterations):threshold(threshold), CCStopCondition(nIterations){}
    
    virtual ~CCStopCondition_Threshold(){}
    
    virtual bool stop(_Solution<int*,float>* solution){        
        auto aux =  CCStopCondition::stop(solution);
        return aux || solution->evaluate() > this->threshold;        
    }
    
    
private:
    const float threshold;
};

#endif /* CCSTOPCONDITION_THRESHOLD_H */