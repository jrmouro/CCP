#include "CCGraphNodo.h"
#include "CCGraphAdjacency.h"

CCGraphNodo::CCGraphNodo(int weight):weight(weight){}
    
CCGraphNodo::~CCGraphNodo(){}
    
int CCGraphNodo::GetWeight() const {
    return weight;
}

void CCGraphNodo::addAdjacency(const CCGraphAdjacency& adjacency){
    this->adjacency.insert(adjacency);
}

void CCGraphNodo::listAdjacency((void (*fun)(const CCGraphAdjacency&))){

    std::for_each(adjacency.begin(), adjacency.end(), fun);

}

int CCGraphNodo::adjacencyWeight(){
        
    int s = 0;

    this->listAdjacency([s&](CCGraphAdjacency ajd){
        s += adj.GetWeight();
    });

    return s;

}