#ifndef CCGRAPHNODO_H
#define CCGRAPHNODO_H

#include <map>
#include <utility>
#include <ostream>
#include <algorithm>

class CCGraphNodo {
public:

    CCGraphNodo(int label, int weight) : label(label), weight(weight) {
    }

    ~CCGraphNodo() {
    }

    int GetWeight() const {
        return weight;
    }

    int GetLabel() const {
        return label;
    }

    void SetWeight(int weight) {
        this->weight = weight;
    }

    void SetAdjacency(int nodo, int weight) {
        this->adjacency[nodo] = weight;
    }

    bool IsAdjacency(int nodo) {
        auto it = adjacency.find(nodo);
        return it != adjacency.end();
    }
    
    int AdjacencyWeight(int nodo)const {
       
        auto it = adjacency.find(nodo);
        
        if(it != adjacency.end()){
            return it->second;
        };

        return 0;

    }

    int AdjacencyWeight()const {

        int s = 0;

        std::for_each(adjacency.begin(), adjacency.end(), [&s](const std::pair<int, int>& pair) {
            s += pair.second;
        });

        return s;

    }

    friend std::ostream& operator<<(std::ostream& os, const CCGraphNodo& obj) {

        os << obj.GetLabel() << " (" << obj.GetWeight() << ")" << std::endl;

        std::for_each(obj.adjacency.begin(), obj.adjacency.end(), [&os](const std::pair<int, int>& pair) {
            os << "  :" << pair.second << " -> " << pair.first << std::endl;
        });

        return os;

    }

private:
    int label, weight;
    std::map<int, int> adjacency;
};


#endif /* CCGRAPHNODO_H */

