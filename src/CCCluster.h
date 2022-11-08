#ifndef CCCLUSTER_H
#define CCCLUSTER_H

#include <vector>
#include "_Evaluable.h"
#include "CCGraph.h"

class CCCluster : public _Evaluable<int> {
public:

    CCCluster(CCGraph* graph) :
    _Evaluable<int>(0),
    representation(graph->GetSize(), 0),
    graph(graph) {
    }

    virtual ~CCCluster() {
    }

    int reevaluate() {

        int ret = 0;

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

    friend std::ostream& operator<<(std::ostream& os, const CCCluster& obj) {

        std::vector<int>::const_iterator iti;

        int nodo = 0;
        for (iti = obj.representation.begin(); iti != obj.representation.end(); ++iti) {
            int i = *iti;

            if (i == 1) os << nodo << " ";

            nodo++;

        }

        os << std::endl;

        return os;

    }

    void AddNodo(int nodo) {

        if (this->representation.at(nodo) == 0) {

            this->representation.at(nodo) = 1;

            int s = 0;

            this->graph->ListEdgesByNodo(nodo, [nodo, this, &s](int dst, int w) {

                if (this->representation.at(dst) == 1) {

                    s += w + this->graph->EdgeWeight(dst, nodo);

                }

            });

            this->evaluation += s;

        }

    }

    void SwapNodo(int nodo) {
        
        if (this->representation.at(nodo) == 0) {
            
            this->AddNodo(nodo);
            
        } else {
            
            this->DelNodo(nodo);
        
        }
        
    }
    
    void SetNodo(int nodo, int value){
        if(value == 0)
            DelNodo(nodo);
        else
            AddNodo(nodo);
    }

    void DelNodo(int nodo) {

        if (this->representation.at(nodo) == 1) {

            this->representation.at(nodo) = 0;

            int s = 0;

            this->graph->ListEdgesByNodo(nodo, [nodo, this, &s](int dst, int w) {

                if (this->representation.at(dst) == 1) {

                    s += w + this->graph->EdgeWeight(dst, nodo);

                }



            });

            this->evaluation -= s;

        }

    }

    std::vector<int> GetRepresentation() const {
        return representation;
    }

    int GetNodoInto(int nodo) const{
        return representation.at(nodo);
    }


private:

    CCGraph *graph;
    std::vector<int> representation;

};


#endif /* CCCLUSTER_H */

