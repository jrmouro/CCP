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
        int nCluster = ccinstance->GetNClusters();
        std::vector<int> wCluster(nCluster, 0);
        int cMin = 0;
        std::vector<bool> minCluster(nCluster, false);
        int roulette = 0;

        ccinstance->GetGraph()->ListNodos(

                [&roulette, &cMin, &minCluster, nCluster, &wCluster, &ret, ccinstance](int nodo, int weight) { // para cada nó
                    
                    bool flag = false; // para saber se o nó foi alocado segundo a heurística
                    
                    for (int i = 0; i < nCluster; i++) { // percorro todos os clusters

                        if (cMin < nCluster) { // se ainda existe cluster que não atigiu o limite mínimo

                            if (minCluster.at(i)) { // vou buscar o primeiro cluster que não atingiu
                                
                                continue;
                                
                            } else { // e aloco o nó nele

                                
                                wCluster.at(i) = wCluster.at(i) + weight;
                                
                                if(wCluster.at(i) >= ccinstance->GetLowerClusterLimit(i)){
                                    
                                    minCluster.at(i) = true;
                                    cMin++;
                                    
                                }
                                
                                ret->setNodo(nodo, 1, i);
                                
                                flag = true;

                                break;
                            }

                        } else { // se todos os clusters atingiram o limite mínimo

                            int aux = wCluster.at(i) + weight;

                            if (aux <= ccinstance->GetUpperClusterLimit(i)) { // vou buscar o primeiro cluster que é compatível para alocação em relação ao limite máximo

                                wCluster.at(i) = aux;
                                ret->setNodo(nodo, 1, i);
                                
                                flag = true;

                                break;

                            } else {

                                continue;

                            }

                        }

                    }
                    
                    if(!flag){ // se o nó não foi allocado ainda, ele o será em um cluster segundo a roleta
                        
                        ret->setNodo(nodo, 1, roulette);
                        
                        roulette++;
                                
                        if(roulette == nCluster){
                            
                            roulette = 0;

                        }
                        
                    }
                    
                });

        return ret;

    }
};

#endif /* CCBUILDERSOLUTION_H */

