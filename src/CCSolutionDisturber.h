#ifndef _CCSOLUTIONDISTURB_H
#define _CCSOLUTIONDISTURB_H

#include "_SolutionDisturber.h"

class CCSolutionDisturber: public _SolutionDisturber<int*, float>{

    public:
    CCSolutionDisturber(double rate):_SolutionDisturber<int*, float>(), rate(rate) {}
    CCSolutionDisturber(int seed, float rate):_SolutionDisturber<int*, float>(seed), rate(rate) {}
    virtual ~CCSolutionDisturber(){}
    virtual _Solution<int*, float>* solve(_Solution<int*, float>* solution){
        
        CCSolution *ccSolution = (CCSolution *)solution;
        auto ret = new CCSolution(ccSolution);
        int nClusters = ccSolution->GetInstance()->GetNClusters();
        int size = ccSolution->GetInstance()->GetSize();        
        int repeat = (int)std::round(size * rate);
        
        for(int z = 0; z < repeat; z++){
            
            int n = this->GetRandomValue(0, size);
            int i = this->GetRandomValue(0, nClusters);
            int j = this->GetRandomValue(0, nClusters);
            
            ret->SwapNodo(n, i, j);
            
        }
        
        return ret;
    }
    
private:
    float rate;
};

#endif /* _CCSOLUTIONDISTURB_H */

