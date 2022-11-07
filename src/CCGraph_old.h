#ifndef CCGRAPH_H
#define CCGRAPH_H

#include <vector>

#include "CCGraphNodo.h"
#include "CCGraphAdjacency.h"


class CCGraph{
public:
    
    CCGraph(int size):size(size){
    
        weights = new int(size);
        adjacencyMatrix = new int(size * size);
        
    }
    
    virtual ~CCCluster() {
        delete [] weights;
        delete [] adjacencyMatrix;
    }
    
     int GetAdjacency(int nodo1, int nodo2) const {
        return this->adjacencyMatrix[nodo1][nodo2];
    }

    int GetSize() const {
        return size;
    }

    int GetWeight(int nodo) const {
        return weights[nodo];
    }
    
    void addNodo(int index){
        
    }
    
private:
    
    std::map<int, CCGraphNodo> nodos;
    std::vector<CCGraphAdjacency> adjacency;
    
};

#endif /* CCGRAPH_H */

