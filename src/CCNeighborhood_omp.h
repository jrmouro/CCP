#ifndef CCNEIGHBORHOOD_H
#define CCNEIGHBORHOOD_H

#include <vector>
#include <iostream>
#include "_Neighborhood_Algorithm.h"
#include "_Solution.h"
#include "CCSolution.h"

class CCNeighborhood : public _Neighborhood_Algorithm<float>{
public:
    
    CCNeighborhood(){}
    CCNeighborhood(const CCNeighborhood& other){}
    
    virtual ~CCNeighborhood() {}
    
    virtual std::vector<_Solution<float>*>* solvev(const _Solution<float>& solution) const{

        int nClusters = ((const CCSolution&)solution).GetInstance().GetNClusters();
        int size = ((const CCSolution&)solution).GetInstance().GetSize();

        std::vector<_Solution<float>*>* ret = new std::vector<_Solution<float>*>();
        ret->reserve(size*nClusters*nClusters);
        
        for (int n = 0; n < size; n++){

            for (int i = 0; i < nClusters - 1; i++){

                for (int j = 0; j < nClusters; j++){

                    // auto s = new CCSolution((const CCSolution&)solution);

                    auto s = (CCSolution*)solution.clone();

                    float aux = s->SwapNodo(n, i, j);

                    if (aux > 0.0){
                        ret->push_back(s);
                    }else{
                        delete s;
                    }
                    
                }
            }
        }

        return ret;
        
    }
    
    virtual CCNeighborhood* clone(){
        return new CCNeighborhood();
    }
};

#endif /* CCNEIGHBORHOOD_H */