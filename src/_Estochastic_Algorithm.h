#ifndef _ESTOCHASTIC_ALGORITHM_H
#define _ESTOCHASTIC_ALGORITHM_H

#include <chrono>
#include <random>
#include "_Algorithm.h"

class _Estochastic_Algorithm : public _Algorithm{
    
public:
    
    _Estochastic_Algorithm(){}
    _Estochastic_Algorithm(unsigned seed):seed(seed){}
    _Estochastic_Algorithm(const _Estochastic_Algorithm& other) :seed(other.seed) {}
    _Estochastic_Algorithm& operator=(const _Estochastic_Algorithm& right) {
        if (this == &right)
            return *this;
        this->seed = right.seed;
        return *this;
    }
    
    virtual ~_Estochastic_Algorithm() {}
    
    virtual int NextRandomInt(int offset, int range){
        srand(seed); 
        int ret = offset + rand()%range;
        seed = rand();
        return ret;        
    }
    
    unsigned GetSeed() const {
        return seed;
    }

    void SetSeed(unsigned seed) {
        this->seed = seed;
    }

    virtual int NextSeed(){
        srand(seed); 
        seed = rand();
        return seed;
    }
    
private:
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
};

#endif /* _ESTOCHASTIC_ALGORITHM_H */

