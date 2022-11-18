#ifndef _CCSOLUTIONDISTURB_H
#define _CCSOLUTIONDISTURB_H

#include "_Solution_Disturber.h"

class CCSolutionDisturber: public _Solution_Disturber<float>{

public:
    CCSolutionDisturber(float rate, float decay, unsigned amount):
            _Solution_Disturber<float>(amount),
            decay(decay),  
            rate(rate) {}
            
    CCSolutionDisturber(float rate,  float decay, unsigned amount, int seed):
            _Solution_Disturber<float>(amount, seed),
            decay(decay), 
            rate(rate) {}
    CCSolutionDisturber(const CCSolutionDisturber& other) :  
            _Solution_Disturber<float>(other), 
            decay(other.decay), 
            rate(other.rate) {}
    
    virtual ~CCSolutionDisturber(){}
    
    virtual _Solution<float>* solve(const _Solution<float>& solution){
        
        auto ret = new CCSolution((const CCSolution&)solution);
        int nClusters = ((CCSolution&)solution).GetInstance().GetNClusters();
        int size = ((CCSolution&)solution).GetInstance().GetSize();        
        int repeat = (int)std::round(size * rate) - (int)std::round(size * (float)_decay++ * decay);
        
        for(int z = 0; z < repeat; z++){
            
            int n = NextRandomInt(0, size);
            int i = NextRandomInt(0, nClusters);
            int j = NextRandomInt(0, nClusters);
            
            ret->SwapNodo(n, i, j);
            
        }
        
        return ret;
    }
    
    virtual std::vector<_Solution<float>*>* solvev(const _Solution<float>& solution) {
        reset();
        return _Solution_Disturber<float>::solvev(solution);
    }
    
    virtual CCSolutionDisturber* clone(){
        return new CCSolutionDisturber(*this);
    }
    
    virtual void reset(){
        _decay = 0;
    }
    
private:
    float rate;
    float decay;
    unsigned _decay = 0;
};

#endif /* _CCSOLUTIONDISTURB_H */

