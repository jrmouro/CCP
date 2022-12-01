#ifndef _ESTOCHASTIC_H
#define _ESTOCHASTIC_H

#include <chrono>
#include <random>
#include "_Resetable.h"

class _Estochastic:public _Resetable{
    
public:
    
    _Estochastic(unsigned seed):currentSeed(seed), initialSeed(seed){ }
        
    _Estochastic(const _Estochastic& other) : initialSeed(other.initialSeed), currentSeed(other.currentSeed) { }
        
    virtual ~_Estochastic() { }
    
    int NextInt(int offset, int range){
        srand(currentSeed); 
        currentSeed = rand(); 
        return offset + currentSeed%range;        
    }
    
    unsigned GetCurrentSeed() const {
        
        return currentSeed;
        
    }
    
    unsigned GetInitialSeed() const {
        return initialSeed;
    }
    
    
    virtual void reset(){
        
        currentSeed = initialSeed;
        
    }
       
    
private:
    
    unsigned initialSeed, currentSeed;
        
};



#endif /* _ESTOCHASTIC_H */

