#ifndef CCSTOPCONDITION_H
#define CCSTOPCONDITION_H

#include "_StopCondition.h"
#include "_Solution.h"

class CCStopCondition : public _StopCondition<int*,float>{
public:
    
    CCStopCondition(int nIterations):nIterations(nIterations){}
    
    virtual ~CCStopCondition(){}
    
    virtual bool stop(_Solution<int*,float>* solution){        
        current++;             
        return !(current < nIterations);        
    }
    
    virtual void reset(){        
        current = 0;        
    }
private:
    int nIterations, current = 0;
};

#endif /* CCSTOPCONDITION_H */

