#include "CCGraphAdjacency.h"
#include "CCGraphNodo.h"

CCGraphAdjacency::CCGraphAdjacency(
            const CCGraphNodo& nodo, 
            int weight):nodo(nodo), weight(weight){}
    
CCGraphAdjacency::~CCGraphAdjacency(){}
    
CCGraphNodo CCGraphAdjacency::GetNodo() const {
    return nodo;
}

int CCGraphAdjacency::GetWeight() const {
    return weight;
}