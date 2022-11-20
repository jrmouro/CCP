#ifndef CCCLUSTER_H
#define CCCLUSTER_H

#include <vector>
#include "_Evaluable.h"
#include "CCGraph.h"

class CCCluster : public _Evaluable<float> {
public:

    CCCluster(const CCGraph& graph) :
        _Evaluable<float>(0.0),
        representation(graph.GetSize(), 0),
        graph(graph) { }
        
    CCCluster(const CCCluster& other) : 
        _Evaluable<float>(other),
        totalNodoWeight(other.totalNodoWeight),
        graph(other.graph), 
        representation(other.representation) { }

//    CCCluster(CCCluster* other) : 
//        _Evaluable<float>(other),
//        totalNodoWeight(other->totalNodoWeight),
//        graph(other->graph),            
//        representation(other->representation) { }

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


            this->graph.ListEdgesByNodo(nodo, [nodo, this, &s](int dst, float w) {

                if (this->representation.at(dst) == 1) {

                    s += w + this->graph.EdgeWeight(dst, nodo);

                }

            });

//            this->evaluation += s;
            
            this->SetEvaluation(this->GetEvaluation() + s);
            
            this->totalNodoWeight += this->graph.NodoWeight(nodo);
                        
        }
        
        *nodoWeight = this->totalNodoWeight;
        
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

            this->graph.ListEdgesByNodo(nodo, [nodo, this, &s](int dst, int w) {

                if (this->representation.at(dst) == 1) {

                    s += w + this->graph.EdgeWeight(dst, nodo);

                }

            });

//            this->evaluation -= s;
            
            this->SetEvaluation(this->GetEvaluation() - s);
            
            this->totalNodoWeight -= this->graph.NodoWeight(nodo);
            

        }
        
        *nodoWeight = this->totalNodoWeight;
        
        return -s;

    }

    std::vector<int> GetRepresentation() const {
        return representation;
    }

    int GetNodo(int nodo) const{
        return representation.at(nodo);
    }
    
    int GetNodoWeight() const {
        return totalNodoWeight;
    }
    
    float reevaluate() {

        float ret = 0;
        
        for(int i = 0; i < representation.size(); i++){
            if(representation.at(i) == 1)
                for(int j = 0; j < representation.size(); j++){
                    if(representation.at(j) == 1)
                        ret += this->graph.EdgeWeight(i, j);
                }
        }

        return ret;

    }

    
    virtual CCCluster* clone() const{
        
        return new CCCluster(*this);
        
    }
    
private:

    int totalNodoWeight = 0;
    const CCGraph& graph;
    std::vector<int> representation;
    
};


#endif /* CCCLUSTER_H */

