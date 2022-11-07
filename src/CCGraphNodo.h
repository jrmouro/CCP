#ifndef CCGRAPHNODO_H
#define CCGRAPHNODO_H

#include <set>
#include <algorithm>

#include "CCGraphAdjacency.h"

class CCGraphAdjacency;

class CCGraphNodo{
public:
    
    CCGraphNodo(int weight);
    
    virtual ~CCGraphNodo();
    
    int GetWeight();
    
    void addAdjacency(const CCGraphAdjacency& adjacency);
    
    void listAdjacency(void (*fun)(const CCGraphAdjacency&));
    
    int adjacencyWeight(){
        
        int s = 0;
        
        this->listAdjacency([s&](CCGraphAdjacency ajd){
            s += adj.GetWeight();
        });
        
        return s;
        
    }

private:
    int weight;  
    std::set<CCGraphAdjacency> adjacency;
};


#endif /* CCGRAPHNODO_H */

