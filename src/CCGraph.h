#ifndef CCGRAPH_H
#define CCGRAPH_H

#include <vector>
#include <functional>


class CCGraph {
public:

    CCGraph(int size) : size(size) {
        
        if(this->size > 0){

            this->adjMatrix = new float*[size];
            this->nodosWeight = new int[size];

            for (int i = 0; i < size; i++) {

                this->nodosWeight[i] = 0;
                this->adjMatrix[i] = new float[size];

                for (int j = 0; j < size; j++) {

                    this->adjMatrix[i][j] = 0.0;

                }

            }
        
        }
        
    }
    
    CCGraph(const CCGraph& other) :
    
        size(other.size){
        
        this->adjMatrix = new float*[size];
        this->nodosWeight = new int[size];
        
        for (int i = 0; i < size; i++) {

            this->nodosWeight[i] = other.nodosWeight[i];
            this->adjMatrix[i] = new float[size];

            for (int j = 0; j < size; j++) {

                this->adjMatrix[i][j] = other.adjMatrix[i][j];

            }

        }
        
    }
    
    CCGraph& operator=(const CCGraph& right) {
        // Check for self-assignment!
        if (this == &right) // Same object?
            return *this; // Yes, so skip assignment, and just return *this.
        
        if(this->size > 0){
        
            for (int j = 0; j < size; j++) {

                delete adjMatrix[j];

            }

            delete [] this->adjMatrix;
            delete [] this->nodosWeight;
        
        }
        
        this->size = right.size;
        
        if(this->size > 0){
        
            this->adjMatrix = new float*[right.size];
            this->nodosWeight = new int[right.size];

            for (int i = 0; i < right.size; i++) {

                this->nodosWeight[i] = right.nodosWeight[i];
                this->adjMatrix[i] = new float(right.size);

                for (int j = 0; j < right.size; j++) {

                    this->adjMatrix[i][j] = right.adjMatrix[i][j];

                }

            }
            
        }
        
        return *this;
    }

    

    int GetSize() const {
        return size;
    }

    void SetNodo(int nodoLabel, int weight) {

        this->nodosWeight[nodoLabel] = weight;

    }

    bool AddEdge(int nodoLabel1, int nodoLabel2, float weight) {

        this->adjMatrix[nodoLabel1][nodoLabel2] = weight;

        return true;

    }
    
    int NodoWeight(int nodoLabel) const{

        return this->nodosWeight[nodoLabel];

    }

    float EdgeWeight(int nodoLabel1, int nodoLabel2) const {

        return this->adjMatrix[nodoLabel1][nodoLabel2];

    }

    void ListEdgesByNodo(int origLabel, std::function<void(int dstLabel, float weight)> functor)const {

        for (int j = 0; j < size; j++) {
            
            functor(j, adjMatrix[origLabel][j]);

        }

    }
    
    void ListEdges(std::function<void(int origLabel, int dstLabel, float weight)> functor) const {

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {

                functor(i, j, adjMatrix[i][j]);

            }
        }

    }
    
    void ListNodos(std::function<void(int nodoLabel, int weight)> functor) const {

        for (int j = 0; j < size; j++) {
            
            functor(j, nodosWeight[j]);

        }

    }

    virtual ~CCGraph() {
        
        if(this->size > 0){

            for (int j = 0; j < size; j++) {

                delete adjMatrix[j];

            }

            delete [] this->adjMatrix;
            delete [] this->nodosWeight;
        
        }

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
    float **adjMatrix;
    int *nodosWeight;

};

#endif /* CCGRAPH_H */

