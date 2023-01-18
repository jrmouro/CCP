#ifndef CCNEIGHBORHOOD_H
#define CCNEIGHBORHOOD_H

#include <vector>
#include <iostream>
#include "_Solution_Comparator.h"
#include "_Neighborhood_Algorithm.h"
#include "_Solution.h"
#include "CCSolution.h"

class CCNeighborhood : public _Neighborhood_Algorithm<float>{
public:
    
    CCNeighborhood(const _Solution_Comparator<float>& solutionComparator):
    solutionComparator(solutionComparator){}
    
    CCNeighborhood(const CCNeighborhood& other):solutionComparator(other.solutionComparator){}
    
    virtual ~CCNeighborhood() {}
    
    virtual std::vector<_Solution<float>*>* solvev(const _Solution<float>& solution) {

        int nClusters = ((const CCSolution&)solution).GetInstance().GetNClusters();
        int size = ((const CCSolution&)solution).GetInstance().GetSize();

        std::vector<_Solution<float>*>* ret = new std::vector<_Solution<float>*>();
        ret->reserve(size*nClusters*nClusters);
        
        for (int n = 0; n < size; n++){

            for (int i = 0; i < nClusters - 1; i++){

                for (int j = 0; j < nClusters; j++){

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
    
    virtual _Solution<float>* solve(const _Solution<float>& solution) {
        
        auto ret = solution.clone();

        int nClusters = ((const CCSolution&)solution).GetInstance().GetNClusters();
        int size = ((const CCSolution&)solution).GetInstance().GetSize();
        
        for (int n = 0; n < size; n++){

            for (int i = 0; i < nClusters - 1; i++){

                for (int j = 0; j < nClusters; j++){

                    auto s = (CCSolution*)solution.clone();

                    float aux = s->SwapNodo(n, i, j);
                    
                    if(this->solutionComparator(*s, *ret)){
                        
                        delete ret;
                        ret = s;
                        
                    } else {
                        
                        delete s;
                        
                    }                    
                }
            }
        }

        return ret;
        
    }
    
    virtual CCNeighborhood* clone(){
        return new CCNeighborhood(*this);
    }
    
    protected:
    
        const _Solution_Comparator<float>& solutionComparator;
    
};

#endif /* CCNEIGHBORHOOD_H */