#ifndef CCINSTANCE_H
#define CCINSTANCE_H

#include <unordered_map>

#include "src/CCGraph.h"

class CCInstance : public _Instance{
public:
    
    CCInstance(std::string filename){
    
        // ?
    
    }
    
    virtual ~CCInstance() {}
    
     int GetClustersSize() const {
        return clustersSize;
    }

    int GetLowerClusterLimit() const {
        return lowerClusterLimit;
    }

    int* GetMatrix() const {
        return matrix;
    }

    int GetNClusters() const {
        return nClusters;
    }

    int GetNElements() const {
        return nElements;
    }

    int* GetNodoWeights() const {
        return nodoWeights;
    }

    int GetUpperClusterLimit() const {
        return upperClusterLimit;
    }

    
private:
    
    int nElements;
    int nClusters;
    int clustersSize; // 0 -> ss, i -> ds
    int lowerClusterLimit;
    int upperClusterLimit; 
    
    int* nodoWeights;
    int* adjacencyMatrix;
    
     
    
};

#endif /* CCINSTANCE_H */

