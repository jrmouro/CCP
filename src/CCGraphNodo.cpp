#include <map>
#include <utility>
#include <algorithm>
#include <ostream>
#include "CCGraphNodo.h"

CCGraphNodo::CCGraphNodo(int label, int weight):label(label), weight(weight){}
    
CCGraphNodo::~CCGraphNodo(){}
    
int CCGraphNodo::GetWeight() const {
    return weight;
}

int CCGraphNodo::GetLabel() const {
    return label;
}

void CCGraphNodo::SetWeight(int weight) {
    this->weight = weight;
}


void CCGraphNodo::addAdjacency(int nodo, int weight){
    this->adjacency[nodo] = weight;
}

int CCGraphNodo::adjacencyWeight()const{
        
    int s = 0;

    std::for_each(adjacency.begin(), adjacency.end(), [&s](const std::pair<int,int>& pair){
        s += pair.second;
    });
    
    return s;

}

std::ostream& operator<<(std::ostream& os, const CCGraphNodo& obj) {

    os << obj.GetLabel() << " (" << obj.GetWeight() << ")" << std::endl;
        
    std::for_each(obj.adjacency.begin(), obj.adjacency.end(), [&os](const std::pair<int,int>& pair){
        os << "  :" << pair.second << " -> " << pair.first << std::endl;
    });

    return os;
    
}   