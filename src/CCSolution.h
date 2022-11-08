#ifndef CCSOLUTION_H
#define CCSOLUTION_H

#include "_Solution.h"
#include "CCCluster.h"
#include "CCInstance.h"

class CCSolution: public _Solution<int*, int> {
public:
    
    CCSolution(CCInstance *instance):instance(instance){
    
        int nClusters = instance->GetNClusters();
        
        for(int i = 0; i < nClusters; i++){
            
            clusters.push_back(new CCCluster(instance->GetGraph()));
            
        }
    
    }
        
    virtual ~CCSolution(){
        if(representation != nullptr) delete [] representation;
    }
    
    virtual int* representation() const{ 
        return representation; 
    }
    
    virtual int reevaluate(){
        
    }
    
    void setNodo(int nodo, int value, int cluster){
        this->clusters.at(cluster)->SetNodo(nodo, value);
    }
    
    void SwapNodo(int nodo, int cluster){
        this->clusters.at(cluster)->SwapNodo(nodo);
    }
    
private:
    
    /*
     * Representation
     * vSolution, nClusters, vCluster_0, nNodoCluster_0, nodosCluster_0, 
     * vCluster_1, nNodoCluster_1, nodosCluster_1, ... 
     * ... vCluster_n-1, nNodoCluster_n-1, nodosCluster_n-1     
     */
    
    std::vector<CCCluster*> clusters;
    int* representation = nullptr;
    CCInstance *instance;    
    
};

#endif /* CCSOLUTION_H */

