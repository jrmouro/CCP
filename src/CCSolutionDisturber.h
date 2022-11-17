#ifndef _CCSOLUTIONDISTURB_H
#define _CCSOLUTIONDISTURB_H

#include "_Solution_Disturber.h"

class CCSolutionDisturber: public _Solution_Disturber<float>{

public:
    CCSolutionDisturber(double rate, unsigned amount = 1):_Solution_Disturber<float>(amount), rate(rate) {}
    CCSolutionDisturber(int seed, unsigned amount, float rate):_Solution_Disturber<float>(amount, seed), rate(rate) {}
    CCSolutionDisturber(const CCSolutionDisturber& other) :  
            _Solution_Disturber<float>(other), 
            rate(other.rate) {}
    virtual ~CCSolutionDisturber(){}
    
    virtual _Solution<float>* solve(const _Solution<float>& solution){
        
        auto ret = new CCSolution((const CCSolution&)solution);
        int nClusters = ((CCSolution&)solution).GetInstance().GetNClusters();
        int size = ((CCSolution&)solution).GetInstance().GetSize();        
        int repeat = (int)std::round(size * rate);
        
        for(int z = 0; z < repeat; z++){
            
            int n = NextRandomInt(0, size);
            int i = NextRandomInt(0, nClusters);
            int j = NextRandomInt(0, nClusters);
            
            ret->SwapNodo(n, i, j);
            
        }
        
        return ret;
    }
    
    virtual CCSolutionDisturber* clone(){
        return new CCSolutionDisturber(*this);
    }
    
private:
    float rate;
};

#endif /* _CCSOLUTIONDISTURB_H */

