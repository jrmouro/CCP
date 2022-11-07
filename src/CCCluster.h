#ifndef CCCLUSTER_H
#define CCCLUSTER_H

#include <set>
#include "_Evaluable.h"
#include "CCGraph.h"

class CCCluster : public _Evaluable<int> {
public:

    CCCluster(CCGraph *graph) : graph(graph) {
    }

    virtual ~CCCluster() {
    }

    int reevaluate() {

        int ret = 0;

        std::set<int>::iterator iti;
        for (iti = nodos.begin(); iti != nodos.end(); ++iti) {
            int i = *iti;
            std::set<int>::iterator itj;
            for (itj = nodos.begin(); itj != nodos.end(); ++itj) {
                int j = *itj;

                ret += this->graph->EdgeWeight(i, j);

            }
        }
        
        return ret;

    }

    friend std::ostream& operator<<(std::ostream& os, const CCCluster& obj) {

        std::set<int>::iterator iti;
        for (iti = obj.nodos.begin(); iti != obj.nodos.end(); ++iti) {
            int i = *iti;
            os << i << " ";
        }

        os << std::endl;

        return os;

    }

    void AddNodo(int nodo) {

        std::set<int>::iterator it = this->nodos.find(nodo);

        if (it == this->nodos.end()) {

            this->nodos.insert(nodo);

            int s = 0;

            this->graph->ListEdge(nodo, [nodo, this, &s](int dst, int w) {

                s += w + this->graph->EdgeWeight(dst, nodo);

            });

            this->evaluation += s;

        }

    }

    void DelNodo(int nodo) {

        this->nodos.erase(nodo);

    }


private:

    CCGraph *graph;
    std::set<int> nodos;

};


#endif /* CCCLUSTER_H */

