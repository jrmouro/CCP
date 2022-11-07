#ifndef CCGRAPH_H
#define CCGRAPH_H

#include <vector>
#include <map>
#include <functional>

#include "CCGraphNodo_old.h"

class CCGraph {
public:

    int GetSize() const {
        return size;
    }

    CCGraph(int size) : size(size) {

        this->adjMatrix = new int*[size];
        this->nodosWeight = new int[size];

        for (int i = 0; i < size; i++) {

            this->nodosWeight[i] = 0;
            this->adjMatrix[i] = new int(size);

            for (int j = 0; j < size; j++) {

                this->adjMatrix[i][j] = 0;

            }

        }

    }

    void SetNodo(int label, int weight) {

        this->nodosWeight[label] = weight;

    }

    bool AddEdge(int nodoLabel1, int nodoLabel2, int weight) {

        this->adjMatrix[nodoLabel1][nodoLabel2] = weight;

        return true;

    }

    int EdgeWeight(int nodoLabel1, int nodoLabel2) {

        return this->adjMatrix[nodoLabel1][nodoLabel2];

    }

    void ListEdge(int orig, std::function<void(int dst, int weight)> functor) {

        for (int j = 0; j < size; j++) {
            
            functor(j, adjMatrix[orig][j]);

        }

    }

    virtual ~CCGraph() {

        for (int j = 0; j < size; j++) {

            delete adjMatrix[j];

        }

        delete [] this->adjMatrix;
        delete [] this->nodosWeight;

    }

    friend std::ostream& operator<<(std::ostream& os, const CCGraph& obj) {

        for (int i = 0; i < obj.size; i++) {

            os << i << "(" << obj.nodosWeight[i] << ")" << std::endl;

            for (int j = 0; j < obj.size; j++) {

                os << " --" << obj.adjMatrix[i][j] << "--> " << j << "(" << obj.nodosWeight[j] << ")" << std::endl;

            }

        }

        return os;

    }


private:

    int size;
    int **adjMatrix;
    int *nodosWeight;

};

#endif /* CCGRAPH_H */

