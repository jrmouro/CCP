#ifndef CCSTOPCONDITION_THRESHOLD_H
#define CCSTOPCONDITION_THRESHOLD_H

#include "CCStopCondition.h"
#include "_Solution.h"

class CCStopCondition_Threshold : public CCStopCondition{
public:
    
    CCStopCondition_Threshold(float threshold, int nIterations):threshold(threshold), CCStopCondition(nIterations){}
    CCStopCondition_Threshold(const CCStopCondition_Threshold& other) :
            CCStopCondition(other), 
            threshold(other.threshold) {}
        
    virtual ~CCStopCondition_Threshold(){}
    
    virtual bool stop(const _Solution<float>& solution){        
        auto aux =  CCStopCondition::stop(solution);
        return aux || solution.GetEvaluation() > this->threshold;        
    }
    
    virtual CCStopCondition_Threshold* clone(){
        return new CCStopCondition_Threshold(*this);
    }
        
private:
    const float threshold;
};

#endif /* CCSTOPCONDITION_THRESHOLD_H */