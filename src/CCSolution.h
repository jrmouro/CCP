#ifndef CCSOLUTION_H
#define CCSOLUTION_H

#include "_Solution.h"
#include "CCCluster.h"
#include "CCInstance.h"

class CCSolution : public _Solution<int*, float> {
public:

    CCSolution(CCInstance *instance) : _Solution<int*, float>(0.0), instance(instance), penalty(0) {

        int nClusters = instance->GetNClusters();

        for (int i = 0; i < nClusters; i++) {

            clusters.push_back(new CCCluster(instance->GetGraph()));
            penaltyClusters.push_back(0);
        }

    }
    
    CCSolution(const CCSolution& other) : _Solution<int*, float>(other), instance(other.instance), penalty(other.penalty) {
         
        int nClusters = instance->GetNClusters();

        for (int i = 0; i < nClusters; i++) {

            clusters.push_back(new CCCluster(*other.clusters.at(i)));
            penaltyClusters.push_back(other.penaltyClusters.at(i));

        }        
        
    }
    
    CCSolution(CCSolution* other) : _Solution<int*, float>(other), instance(other->instance), penalty(other->penalty) {
         
        int nClusters = instance->GetNClusters();

        for (int i = 0; i < nClusters; i++) {

            clusters.push_back(new CCCluster( other->clusters.at(i)));
            penaltyClusters.push_back(other->penaltyClusters.at(i));

        }        
        
    }


    virtual ~CCSolution() {
        if (_representation != nullptr) delete [] _representation;
        for(auto c : clusters){
            delete c;
        }
            
    }

    virtual int* representation() const {
        return _representation;
    }

    float setNodo(int nodo, int value, int cluster) {
        
        int nw;
        float aux = this->clusters.at(cluster)->SetNodo(nodo, value, &nw);
        this->evaluation += aux;
        
        int cPenalty = 0;
        
        if(nw < this->instance->GetLowerClusterLimit(cluster)){
            
            cPenalty = this->instance->GetLowerClusterLimit(cluster) - nw;
            
        } else if(nw > this->instance->GetUpperClusterLimit(cluster)){
            
            cPenalty = nw - this->instance->GetUpperClusterLimit(cluster);
            
        }
        
        this->penalty += cPenalty - this->penaltyClusters.at(cluster);
        
        this->penaltyClusters.at(cluster) = cPenalty;
        
        return aux;
        
    }

    float SwapNodo(int nodo, int cluster) {
        
        int nw;
        float aux = this->clusters.at(cluster)->SwapNodo(nodo, &nw);
        this->evaluation += aux;
        
        int cPenalty = 0;
        
        if(nw < this->instance->GetLowerClusterLimit(cluster)){
            
            cPenalty = this->instance->GetLowerClusterLimit(cluster) - nw;
            
        } else if(nw > this->instance->GetUpperClusterLimit(cluster)){
            
            cPenalty = nw - this->instance->GetUpperClusterLimit(cluster);
            
        }
        
        this->penalty += cPenalty - this->penaltyClusters.at(cluster);
        
        this->penaltyClusters.at(cluster) = cPenalty;
        
        return aux;
    }
    
    float SwapNodo(int nodo, int cluster1, int cluster2) {
        
        
        int aux1 = this->clusters.at(cluster1)->GetNodo(nodo);
        int aux2 = this->clusters.at(cluster2)->GetNodo(nodo);
        
        if(aux1 != aux2){
            float f1 = SwapNodo(nodo, cluster1);
            float f2 = SwapNodo(nodo, cluster2);
            return f1 + f2;
        }
        
        return 0;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const CCSolution& obj) {
//        os << "Instance:" << std::endl;
//        os << *obj.instance << std::endl;
        os << "Evaluation: " << obj.GetEvaluation() << std::endl;
        os << "Penalty: " << obj.GetPenalty() << std::endl;
        os << "Clusters:" << std::endl;
        int i = 0;
        for(auto c: obj.clusters){
            os << *c << " - Eval: " << c->GetEvaluation();
            os << " - NodoWeight: " << c->GetNodoWeight();
            os << " - Penalty: " << obj.penaltyClusters.at(i) << std::endl;
            i++;
        }        
        return os;        
    }

    CCInstance* GetInstance() const {
        return instance;
    }

    float GetPenalty()const{
        return (float)penalty/(float)instance->GetWeight();
    }
    
    virtual float reevaluate() {

        float ret = 0;

        std::vector<CCCluster*>::const_iterator iti;

        for (iti = clusters.begin(); iti != clusters.end(); ++iti) {

            CCCluster *c = *iti;

            ret += c->evaluate();

        }

        return ret;

    }
    
private:
    

    /*
     * Representation
     * vSolution, nClusters, vCluster_0, nNodoCluster_0, nodosCluster_0, 
     * vCluster_1, nNodoCluster_1, nodosCluster_1, ... 
     * ... vCluster_n-1, nNodoCluster_n-1, nodosCluster_n-1     
     */

    std::vector<CCCluster*> clusters;
    int* _representation = nullptr;
    CCInstance *instance;
    std::vector<int> penaltyClusters;
    int penalty = 0;

};

#endif /* CCSOLUTION_H */

