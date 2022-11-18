#ifndef _GRASP_OMP_H
#define _GRASP_OMP_H

#include <omp.h>
#include <iostream>
#include "_Grasp.h"
#include "_Solution_Comparator.h"
#include "_Solution_Disturber.h"
#include "_Stop_Condition.h"
#include "_Builder_Solution.h"
#include "_Local_Search.h"

template  <class V> class _Grasp_omp : public _Grasp<V> {
public:
    
    _Grasp_omp( 
            unsigned numThreads,
            _Builder_Solution<V>& builderSolution, 
            _Stop_Condition<V>& stopCondition,
            _Solution_Disturber<V>& solutionDisturber,
            const _Local_Search<V>& localSearch,
            const _Solution_Comparator<V>& solutionComparator):                        
                        _Grasp<V>(
                            builderSolution,
                            stopCondition,
                            solutionDisturber,
                            localSearch,
                            solutionComparator),
                        numThreads(numThreads){
                        
        this->solutionDisturber.SetAmount(numThreads);
                        
                        }
                        
    _Grasp_omp( 
            unsigned numThreads,
            unsigned seed,
            _Builder_Solution<V>& builderSolution, 
            _Stop_Condition<V>& stopCondition,
            _Solution_Disturber<V>& solutionDisturber,
            const _Local_Search<V>& localSearch,
            const _Solution_Comparator<V>& solutionComparator):
                        numThreads(numThreads),
                        _Grasp<V>(
                            seed,
                            builderSolution,
                            stopCondition,
                            solutionDisturber,
                            localSearch,
                            solutionComparator){
    
        this->builderSolution.SetSeed(this->GetSeed());
        this->solutionDisturber.SetSeed(this->GetSeed());
        this->solutionDisturber.SetAmount(numThreads);
        
    }
    
    _Grasp_omp(const _Grasp_omp<V>& other) :
            _Grasp<V>(other),            
            numThreads(other.numThreads){}

                            
    virtual ~_Grasp_omp(){}
    
    virtual _Solution<V>* solve(const _Solution<V>& solution) {
                
        auto ret = solution.clone();
        
        int i = 0; // eliminar
        
        while(!this->stopCondition.stop(*ret)){
            
            auto solv = this->solutionDisturber.solvev(*ret);
                        
            #pragma omp parallel num_threads(this->numThreads)
            {
                
                int threadId = omp_get_thread_num();
                
                auto localSol = solv->at(threadId);
                
                auto lsSol  = this->localSearch.solve(*localSol); 
                
                delete localSol;
                
                if(this->solutionComparator(*lsSol, *ret)){
                    
                    #pragma omp critical
                    {
                
                        delete ret;

                        ret = lsSol;

                        std::cout << i++ << "(" << threadId<< "): " << ret->evaluate() << std::endl; // eliminar
                    
                    }

                } else {

                    delete lsSol;

                }

            }
            
            delete solv;                        
            
        }
        
        return ret;
        
    }
    
    virtual _Solution<V>* solve(const _Instance& instance) {

        auto solution = this->builderSolution.solve(instance);
        
        auto ret = this->solve(*solution);
        
        delete solution;
        
        return ret;

    }
    
    virtual _Grasp_omp* clone(){
        return new _Grasp_omp(*this);
    }
    
protected:
    unsigned numThreads = 1;
            
};

#endif /* _GRASP_OMP_H */

