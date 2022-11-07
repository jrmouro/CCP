#ifndef CCGRAPHADJACENCY_H
#define CCGRAPHADJACENCY_H


#include <ostream>

class CCGraphNodo;

class CCGraphAdjacency{
public:
    
    CCGraphAdjacency(
            CCGraphNodo* nodo, 
            int weight);
    
    virtual ~CCGraphAdjacency();
    
    CCGraphNodo* GetNodo() const;
    
    int GetWeight() const;
    
    friend std::ostream& operator<<(std::ostream& os, const CCGraphAdjacency& obj);

private:
    
    CCGraphNodo* nodo;
    int weight; 
    
};

#endif /* CCGRAPHADJACENCY_H */

