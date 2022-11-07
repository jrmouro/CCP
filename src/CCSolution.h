#ifndef CCSOLUTION_H
#define CCSOLUTION_H

class CCSolution: public _Solution<*int, int> {
public:
    
    CCSolution(const std::vector<int>& representation):
        _Solution<std::vector<int>, int>(),
        representation(representation){}
        
    virtual ~CCSolution(){}
    
    virtual std::vector<int> representation() const{ 
        return representation; 
    }
    
    virtual int reevaluate(){
        
    }
    
private:
    
    /*
     * Representation
     * vSolution, nClusters, vCluster_0, nNodoCluster_0, nodosCluster_0, 
     * vCluster_1, nNodoCluster_1, nodosCluster_1, ... 
     * ... vCluster_n-1, nNodoCluster_n-1, nodosCluster_n-1     
     */
    
    std::vector<int> representation;
    CCInstance *instance = nullptr;
    
    
};

#endif /* CCSOLUTION_H */

