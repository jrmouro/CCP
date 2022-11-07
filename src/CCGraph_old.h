#ifndef CCGRAPH_H
#define CCGRAPH_H

#include <vector>
#include <map>

#include "CCGraphNodo_old.h"

class CCGraph {
    
public:

    void SetNodo(int label, int weight) {
        
        std::map<int, CCGraphNodo*>::iterator it;
        it = this->nodos.find(label);
        
        if (it != this->nodos.end()) {
            
            it->second->SetWeight(weight);
            
        } else {
            
            this->nodos[label] = new CCGraphNodo(label, weight);
            
        }
    }

    bool AddEdge(int nodoLabel1, int nodoLabel2, int weight) {

        std::map<int, CCGraphNodo*>::iterator it1;
        it1 = this->nodos.find(nodoLabel1);

        if (it1 != this->nodos.end()) {

            std::map<int, CCGraphNodo*>::iterator it2;
            it2 = this->nodos.find(nodoLabel2);

            if (it2 != this->nodos.end()) {

                it1->second->SetAdjacency(nodoLabel2, weight);
                it2->second->SetAdjacency(nodoLabel1, weight);

                return true;

            }

        }

        return false;

    }

    virtual ~CCGraph() {
        
        for (auto const& x : nodos) {
            delete x.second;
        }
    }
    
    friend std::ostream& operator<<(std::ostream& os, const CCGraph& obj) {
        
        std::for_each(obj.nodos.begin(), obj.nodos.end(), [&os](const std::pair<int, CCGraphNodo*>& pair) {
            os << *pair.second << std::endl;
        });
        
        return os;
    }


private:

    std::map<int, CCGraphNodo*> nodos;

};

#endif /* CCGRAPH_H */

