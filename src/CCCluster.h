#ifndef CCCLUSTER_H
#define CCCLUSTER_H

class CCCluster : public CCGraph, public _Evaluable<int>{
public:
    
    virtual ~CCInstance() {}
    
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
    
    std::set<int> elementsIndex;
    
    int lowerClusterLimit;
    int upperClusterLimit; 
    
    int* nodoWeights;
    int* matrix;   
    
};


#endif /* CCCLUSTER_H */

