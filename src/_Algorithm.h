#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include <chrono>
#include <random>
#include "_Solution.h"

class _Algorithm {
    
public:
    
    _Algorithm(){}
    _Algorithm(unsigned seed):seed(seed){}
    
    virtual ~_Algorithm() {}
    
    unsigned GetSeed() const {
        return seed;
    }

    void SetSeed(unsigned seed) {
        this->seed = seed;
    }
    
    int GetRandomValue(int offset, int range){
        srand(seed); 
        int ret = offset + rand()%range;
        seed = seed * ret + ret * ret;
        return ret;        
    }

private:
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
};

#endif /* _ALGORITHM_H */

