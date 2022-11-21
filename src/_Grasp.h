#ifndef _GRASP_H
#define _GRASP_H


#include <iostream>
#include "_Estochastic_Solution_Algorithm.h"
#include "_Solution_Comparator.h"
#include "_Solution_Disturber.h"
#include "_Stop_Condition.h"
#include "_Builder_Solution.h"
#include "_Local_Search.h"

template  <class V> class _Grasp : public _Estochastic_Solution_Algorithm<V> {
public:
    
    _Grasp( _Stop_Condition<V>& stopCondition,
            _Solution_Disturber<V>& solutionDisturber,
            const _Local_Search<V>& localSearch,
            const _Solution_Comparator<V>& solutionComparator):
                        _Estochastic_Solution_Algorithm<V>(),
                        stopCondition(stopCondition),
                        solutionDisturber(solutionDisturber),
                        localSearch(localSearch),
                        solutionComparator(solutionComparator){}
                        
    _Grasp( unsigned seed,
            _Stop_Condition<V>& stopCondition,
            _Solution_Disturber<V>& solutionDisturber,
            const _Local_Search<V>& localSearch,
            const _Solution_Comparator<V>& solutionComparator):
                        _Estochastic_Solution_Algorithm<V>(seed),
                        stopCondition(stopCondition),
                        solutionDisturber(solutionDisturber),
                        localSearch(localSearch),
                        solutionComparator(solutionComparator){
    
        this->solutionDisturber.SetSeed(this->GetSeed());
        
    }
    
    _Grasp(const _Grasp<V>& other) :
            _Estochastic_Solution_Algorithm<V>(other), 
            solutionDisturber(other.solutionDisturber), 
            solutionComparator(other.solutionComparator), 
            stopCondition(other.stopCondition), 
            localSearch(other.localSearch) {
    }

                            
    virtual ~_Grasp(){}
    
    virtual _Solution<V>* solve(const _Solution<V>& solution) {
        
        auto ret = solution.clone();
        
//        int i = 0; // eliminar
        
        while(!this->stopCondition.stop(*ret)){
                                    
            auto aux = this->solutionDisturber.solve(*ret);
            
            auto aux2 = this->localSearch.solve(*aux);  
            
            delete aux;
            
            if(this->solutionComparator(*aux2, *ret)){
                
                delete ret;
                
                ret = aux2;
                
//                std::cout << i++ << ": " << ret->evaluate() << std::endl; // eliminar
                
            } else {
                
                delete aux2;
                
                this->solutionDisturber.reset();
                
            }
            
            
        }
        
        return ret;
        
    }
    
    
    virtual _Grasp* clone(){
        return new _Grasp(*this);
    }
    
protected:
    _Solution_Disturber<V>& solutionDisturber;
    const _Solution_Comparator<V>& solutionComparator;
    _Stop_Condition<V>& stopCondition;
    const _Local_Search<V>& localSearch;
            
};

#endif /* _GRASP_H */

