#ifndef CCCLUSTER_H
#define CCCLUSTER_H

#include <vector>
#include "_Evaluable.h"
#include "CCGraph.h"

class CCCluster : public _Evaluable<float> {
public:

    CCCluster(CCGraph* graph) :
        _Evaluable<float>(0.0),
        representation(graph->GetSize(), 0),
        graph(graph) { }
        
    CCCluster(const CCCluster& other) : 
        _Evaluable<float>(other),
        nodoWeight(other.nodoWeight),
        graph(other.graph), 
        representation(other.representation) { }

    CCCluster(CCCluster* other) : 
        _Evaluable<float>(other),
        nodoWeight(other->nodoWeight),
        graph(other->graph),            
        representation(other->representation) { }

    virtual ~CCCluster() { }
    

    friend std::ostream& operator<<(std::ostream& os, const CCCluster& obj) {

        std::vector<int>::const_iterator iti;

        int nodo = 0;
        for (iti = obj.representation.begin(); iti != obj.representation.end(); ++iti) {
            int i = *iti;

            if (i == 1) os << nodo << " ";

            nodo++;

        }

        return os;

    }

    float AddNodo(int nodo, int* nodoWeight) {
        
        float s = 0;

        if (this->representation.at(nodo) == 0) {

            this->representation.at(nodo) = 1;


            this->graph->ListEdgesByNodo(nodo, [nodo, this, &s](int dst, float w) {

                if (this->representation.at(dst) == 1) {

                    s += w + this->graph->EdgeWeight(dst, nodo);

                }

            });

            this->evaluation += s;
            
            this->nodoWeight += this->graph->NodoWeight(nodo);
                        
        }
        
        *nodoWeight = this->nodoWeight;
        
        return s;

    }

    float SwapNodo(int nodo, int* nodoWeight) {
        
        if (this->representation.at(nodo) == 0) {
            
            return this->AddNodo(nodo, nodoWeight);
            
        } else {
            
            return this->DelNodo(nodo, nodoWeight);
        
        }
        
    }
    
    float SetNodo(int nodo, int value, int* nodoWeight){
        if(value == 0)
            return DelNodo(nodo, nodoWeight);
        
        return  AddNodo(nodo, nodoWeight);
    }

    float DelNodo(int nodo, int* nodoWeight) {
        
        float s = 0;

        if (this->representation.at(nodo) == 1) {

            this->representation.at(nodo) = 0;

            this->graph->ListEdgesByNodo(nodo, [nodo, this, &s](int dst, int w) {

                if (this->representation.at(dst) == 1) {

                    s += w + this->graph->EdgeWeight(dst, nodo);

                }

            });

            this->evaluation -= s;
            
            this->nodoWeight -= this->graph->NodoWeight(nodo);
            

        }
        
        *nodoWeight = this->nodoWeight;
        
        return -s;

    }

    std::vector<int> GetRepresentation() const {
        return representation;
    }

    int GetNodo(int nodo) const{
        return representation.at(nodo);
    }
    
    int GetNodoWeight() const {
        return nodoWeight;
    }


private:

    int nodoWeight = 0;
    CCGraph *graph;
    std::vector<int> representation;
    
    float reevaluate() {

        float ret = 0;

        std::vector<int>::iterator iti;
        for (iti = representation.begin(); iti != representation.end(); ++iti) {
            int i = *iti;
            if (i == 1) {
                std::vector<int>::iterator itj;
                for (itj = representation.begin(); itj != representation.end(); ++itj) {
                    int j = *itj;
                    if (j == 1) {
                        ret += this->graph->EdgeWeight(i, j);
                    }

                }
            }
        }

        return ret;

    }

};


#endif /* CCCLUSTER_H */

