#ifndef _GRASP_OMP_H
#define _GRASP_OMP_H

#include <omp.h>
#include <iostream>
#include "_Instance_Algorithm.h"
#include "_Solution_Comparator.h"
#include "_Solution_Disturber.h"
#include "_Stop_Condition.h"
#include "_Builder_Solution.h"
#include "_Local_Search.h"

template  <class V> class _Grasp_omp : public _Instance_Algorithm<V> {
public:
    
    _Grasp_omp( 
            unsigned numThreads,
            _Builder_Solution<V>& builderSolution, 
            _Stop_Condition<V>& stopCondition,
            _Solution_Disturber<V>& solutionDisturber,
            const _Local_Search<V>& localSearch,
            const _Solution_Comparator<V>& solutionComparator):
                        numThreads(numThreads),
                        _Instance_Algorithm<V>(),
                        builderSolution(builderSolution),
                        stopCondition(stopCondition),
                        solutionDisturber(solutionDisturber),
                        localSearch(localSearch),
                        solutionComparator(solutionComparator){}
                        
    _Grasp_omp( 
            unsigned numThreads,
            unsigned seed,
            _Builder_Solution<V>& builderSolution, 
            _Stop_Condition<V>& stopCondition,
            _Solution_Disturber<V>& solutionDisturber,
            const _Local_Search<V>& localSearch,
            const _Solution_Comparator<V>& solutionComparator):
                        numThreads(numThreads),
                        _Instance_Algorithm<V>(seed),
                        builderSolution(builderSolution),
                        stopCondition(stopCondition),
                        solutionDisturber(solutionDisturber),
                        localSearch(localSearch),
                        solutionComparator(solutionComparator){
    
        this->builderSolution.SetSeed(this->GetSeed());
        this->solutionDisturber.SetSeed(this->GetSeed());
        
    }
    
    _Grasp_omp(const _Grasp_omp<V>& other) :
            _Instance_Algorithm<V>(other),
            numThreads(other.numThreads), 
            builderSolution(other.builderSolution), 
            solutionDisturber(other.solutionDisturber), 
            solutionComparator(other.solutionComparator), 
            stopCondition(other.stopCondition), 
            localSearch(other.localSearch) {
    }

                            
    virtual ~_Grasp_omp(){}
    
    virtual _Solution<V>* solve(const _Solution<V>& solution) {
        
//        omp_set_num_threads(this->numThreads);
        
        auto ret = solution.clone();
        
        bool flag = this->stopCondition.stop(*ret);
        
        #pragma omp parallel shared(flag, ret) num_threads(this->numThreads)
        {
            int i = 0; // eliminar
            
            int threadId = omp_get_thread_num();
        
            while(!flag){               
                    
                auto aux = this->solutionDisturber.solve(*ret);                                    

                auto aux2 = this->localSearch.solve(*aux);  

                delete aux;

                if(this->solutionComparator(*aux2, *ret)){
                    
                    #pragma omp critical
                    {

                        delete ret;

                        ret = aux2;

                    }

                    

                } else {

                    delete aux2;

                }
                
                #pragma omp critical
                {
                
                    flag = this->stopCondition.stop(*ret);
                    
                    std::cout << i++ << "(" << threadId<< "): " << ret->GetEvaluation() << std::endl; // eliminar
                
                }

            }
        
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
    _Builder_Solution<V>& builderSolution;
    _Solution_Disturber<V>& solutionDisturber;
    const _Solution_Comparator<V>& solutionComparator;
    _Stop_Condition<V>& stopCondition;
    const _Local_Search<V>& localSearch;
            
};

#endif /* _GRASP_OMP_H */

