#include "CCGraphAdjacency.h"
#include "CCGraphNodo.h"

CCGraphAdjacency::CCGraphAdjacency(
            CCGraphNodo* nodo, 
            int weight):nodo(nodo), weight(weight){}
    
CCGraphAdjacency::~CCGraphAdjacency(){}
    
CCGraphNodo* CCGraphAdjacency::GetNodo() const {
    return nodo;
}

int CCGraphAdjacency::GetWeight() const {
    return weight;
}

std::ostream& operator<<(std::ostream& os, const CCGraphAdjacency& obj) {
    os << obj.GetWeight() << " -> " << obj.GetNodo()->GetLabel();
    os << " (" << obj.GetNodo()->GetWeight() << ")";
    return os;
}