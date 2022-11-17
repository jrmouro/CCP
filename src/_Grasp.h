#ifndef _GRASP_H
#define _GRASP_H


#include <iostream>
#include "_Instance_Algorithm.h"
#include "_Solution_Comparator.h"
#include "_Solution_Disturber.h"
#include "_Stop_Condition.h"
#include "_Builder_Solution.h"
#include "_Local_Search.h"

template  <class V> class _Grasp : public _Instance_Algorithm<V> {
public:
    
    _Grasp( _Builder_Solution<V>& builderSolution, 
            _Stop_Condition<V>& stopCondition,
            _Solution_Disturber<V>& solutionDisturber,
            const _Local_Search<V>& localSearch,
            const _Solution_Comparator<V>& solutionComparator):
                        _Instance_Algorithm<V>(),
                        builderSolution(builderSolution),
                        stopCondition(stopCondition),
                        solutionDisturber(solutionDisturber),
                        localSearch(localSearch),
                        solutionComparator(solutionComparator){}
    _Grasp( unsigned seed,
            _Builder_Solution<V>& builderSolution, 
            _Stop_Condition<V>& stopCondition,
            _Solution_Disturber<V>& solutionDisturber,
            const _Local_Search<V>& localSearch,
            const _Solution_Comparator<V>& solutionComparator):
                        _Instance_Algorithm<V>(seed),
                        builderSolution(builderSolution),
                        stopCondition(stopCondition),
                        solutionDisturber(solutionDisturber),
                        localSearch(localSearch),
                        solutionComparator(solutionComparator){
    
        this->builderSolution.SetSeed(this->GetSeed());
        this->solutionDisturber.SetSeed(this->GetSeed());
        
    }
    
    _Grasp(const _Grasp<V>& other) :
            _Instance_Algorithm<V>(other),
            builderSolution(other.builderSolution), 
            solutionDisturber(other.solutionDisturber), 
            solutionComparator(other.solutionComparator), 
            stopCondition(other.stopCondition), 
            localSearch(other.localSearch) {
    }

                            
    virtual ~_Grasp(){}
    
    virtual _Solution<V>* solve(const _Solution<V>& solution) {
        
        auto ret = solution.clone();
        
        int i = 0; // eliminar
        
        while(!this->stopCondition.stop(*ret)){
            
            auto aux = this->solutionDisturber.solve(*ret);
            
            auto aux2 = this->localSearch.solve(*aux);  
            
            delete aux;
            
            if(this->solutionComparator(*aux2, *ret)){
                
                delete ret;
                
                ret = aux2;
                
            } else {
                
                delete aux2;
                
            }
            
            std::cout << i++ << ": " << ret->evaluate() << std::endl; // eliminar
            
        }
        
        return ret;
        
    }
    
    virtual _Solution<V>* solve(const _Instance& instance) {

        auto solution = this->builderSolution.solve(instance);
        
        auto ret = this->solve(*solution);
        
        delete solution;
        
        return ret;

    }
    
    virtual _Grasp* clone(){
        return new _Grasp(*this);
    }
    
protected:
    _Builder_Solution<V>& builderSolution;
    _Solution_Disturber<V>& solutionDisturber;
    const _Solution_Comparator<V>& solutionComparator;
    _Stop_Condition<V>& stopCondition;
    const _Local_Search<V>& localSearch;
            
};

#endif /* _GRASP_H */

