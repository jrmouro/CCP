#ifndef _GRASP_H
#define _GRASP_H

#include <iostream>
#include "_InstanceAlgorithm.h"
#include "_SolutionComparator.h"
#include "_SolutionDisturber.h"
#include "_StopCondition.h"
#include "_BuilderSolution.h"
#include "_LocalSearch.h"

template  <class R, class V> class _Grasp : public _InstanceAlgorithm<R,V>, public _SolutionAlgorithm<R,V>  {
public:
    _Grasp( _BuilderSolution<R,V>* builderSolution, 
            _StopCondition<R,V>* stopCondition,
            _SolutionDisturber<R,V>* solutionDisturber,
            _LocalSearch<R,V>* localSearch,
            _SolutionComparator<R, V>* solutionComparator):
                        builderSolution(builderSolution),
                        stopCondition(stopCondition),
                        solutionDisturber(solutionDisturber),
                        localSearch(localSearch),
                        solutionComparator(solutionComparator){}
                            
    virtual ~_Grasp(){}
    
    virtual _Solution<R, V>* solve(_Solution<R,V>* solution) {
        
        auto ret = solution;
        
        int i = 0; // eliminar
        
        while(!this->stopCondition->stop(ret)){
            
            auto aux = this->solutionDisturber->solve(ret);
            
            auto aux2 = this->localSearch->solve(aux); 
            
            if(aux != aux2){
                delete aux;
            }
            
            if((*this->solutionComparator)(*aux2, *ret)){
                
                if(ret != solution){
                    delete ret;
                }
                
                ret = aux2;
                
            } else {
                
                delete aux2;
                
            }
            
            std::cout << i++ << ": " << ret->evaluate() << std::endl; // eliminar
            
        }
        
        return ret;
        
    }
    
    virtual _Solution<R, V>* solve(_Instance* instance) {

        auto solution = this->builderSolution->solve(instance);
        
        auto ret = this->solve(solution);
                
        if(ret != solution) delete solution;
        
        return ret;

    }
    
protected:
    _BuilderSolution<R,V>* builderSolution;
    _SolutionDisturber<R,V>* solutionDisturber;
    _SolutionComparator<R, V>* solutionComparator;
    _StopCondition<R,V>* stopCondition;
    _LocalSearch<R,V>* localSearch;
            
};

#endif /* _GRASP_H */

