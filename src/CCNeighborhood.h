#ifndef CCNEIGHBORHOOD_H
#define CCNEIGHBORHOOD_H

#include <vector>
#include "_NeighborhoodAlgorithm.h"
#include "_Solution.h"
#include "CCSolution.h"

class CCNeighborhood : public _NeighborhoodAlgorithm<int *, int>{
public:
    
    virtual ~CCNeighborhood() {}

    virtual std::vector<_Solution<int *, int> *> *solve(_Solution<int *, int> *solution){

        CCSolution *ccSolution = (CCSolution *)solution;
        int nClusters = ccSolution->GetInstance()->GetNClusters();
        int size = ccSolution->GetInstance()->GetSize();

        std::vector<_Solution<int *, int> *> *ret = new std::vector<_Solution<int *, int> *>();

        for (int n = 0; n < size; n++){

            for (int i = 0; i < nClusters - 1; i++){

                for (int j = 0; j < nClusters; j++){

                    auto s = new CCSolution(ccSolution);

                    int aux = s->SwapNodo(n, i, j);

                    if (aux != 0){
                        ret->push_back(s);
                    }else{
                        delete s;
                    }
                    
                }
            }
        }

        return ret;
    }
};

#endif /* CCNEIGHBORHOOD_H */