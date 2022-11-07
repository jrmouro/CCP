#ifndef CCGRAPHADJACENCY_H
#define CCGRAPHADJACENCY_H

class CCGraphNodo;

class CCGraphAdjacency{
public:
    
    CCGraphAdjacency(
            const CCGraphNodo& nodo, 
            int weight);
    
    virtual ~CCGraphAdjacency();
    
    CCGraphNodo GetNodo() const;
    
    int GetWeight() const;

private:
    
    CCGraphNodo nodo;
    int weight; 
    
};

#endif /* CCGRAPHADJACENCY_H */

