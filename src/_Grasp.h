#ifndef _GRASP_H
#define _GRASP_H

#include "_InstanceAlgorithm.h"
#include "_SolutionComparator.h"
#include "_SolutionDisturber.h"
#include "_StopCondition.h"
#include "_BuilderSolution.h"
#include "_LocalSearch.h"

template  <class R, class V> class _Grasp : public _InstanceAlgorithm<R,V> {
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
    
    virtual _Solution<R, V>* solve(_Instance* instance) {

        auto solution = this->builderSolution->solve(instance);
        
        while(!this->stopCondition->stop(solution)){
            
            auto aux = this->solutionDisturber->solve(solution);
            
            aux = this->localSearch->solve(aux);                       
            
            if((*this->solutionComparator)(*aux, *solution)){
                
                solution = aux;
                
            }
            
        }
        
        return solution;

    }
    
private:
    _BuilderSolution<R,V>* builderSolution;
    _SolutionDisturber<R,V>* solutionDisturber;
    _SolutionComparator<R, V>* solutionComparator;
    _StopCondition<R,V>* stopCondition;
    _LocalSearch<R,V>* localSearch;
            
};

#endif /* _GRASP_H */

