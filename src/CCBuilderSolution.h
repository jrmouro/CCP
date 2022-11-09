#ifndef CCBUILDERSOLUTION_H
#define CCBUILDERSOLUTION_H


#include <vector>
#include "_BuilderSolution.h"
#include "CCSolution.h"

class CCBuilderSolution : public _BuilderSolution<int*, float> {
public:

    CCBuilderSolution() :_BuilderSolution<int*, float>(){ }

    virtual ~CCBuilderSolution() { }

    virtual _Solution<int*, float>* solve(_Instance* instance) {

        CCInstance *ccinstance = (CCInstance*) instance;
        CCSolution *ret = new CCSolution(ccinstance);
        int lower = ccinstance->GetLowerClusterLimit();
        int upper = ccinstance->GetUpperClusterLimit();
        int nCluster = ccinstance->GetNClusters();
        std::vector<int> wCluster(nCluster, 0);
        int cMin = 0;
        std::vector<bool> minCluster(nCluster, false);

        ccinstance->GetGraph()->ListNodos(

                [&cMin, &minCluster, nCluster, &wCluster, lower, upper, &ret](int nodo, int weight) {
                    
                    for (int i = 0; i < nCluster; i++) {

                        if (cMin < nCluster) {

                            if (minCluster.at(i)) {
                                
                                continue;
                                
                            } else {

                                
                                wCluster.at(i) = wCluster.at(i) + weight;
                                
                                if(wCluster.at(i) >= lower){
                                    
                                    minCluster.at(i) = true;
                                    cMin++;
                                    
                                }
                                
                                ret->setNodo(nodo, 1, i);

                                break;
                            }

                        } else {

                            int aux = wCluster.at(i) + weight;

                            if (aux <= upper) {

                                wCluster.at(i) = aux;
                                ret->setNodo(nodo, 1, i);

                                break;

                            } else {

                                continue;

                            }

                        }

                    }
                });

        return ret;

    }
};

#endif /* CCBUILDERSOLUTION_H */

