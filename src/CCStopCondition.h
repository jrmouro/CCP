#ifndef CCSTOPCONDITION_H
#define CCSTOPCONDITION_H

#include "_Stop_Condition.h"
#include "_Solution.h"

class CCStopCondition : public _Stop_Condition<float>{
public:
    
    CCStopCondition(int nIterations):nIterations(nIterations){}
    
    CCStopCondition(const CCStopCondition& other) :
            nIterations(other.nIterations), 
            current(other.current) {}

    
    virtual ~CCStopCondition(){}
    
    virtual CCStopCondition* clone(){
        return new CCStopCondition(*this);
    }
    
    virtual bool stop(const _Solution<float>& solution){    
        return !(current++ < nIterations);        
    }
    
    virtual void reset(){        
        current = 0;        
    }
    
private:
    int nIterations, current = 0;
};

#endif /* CCSTOPCONDITION_H */



