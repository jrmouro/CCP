#ifndef _GRASP_OMP_H
#define _GRASP_OMP_H

#include <omp.h>
#include <iostream>
#include "_InstanceAlgorithm.h"
#include "_SolutionComparator.h"
#include "_SolutionDisturber.h"
#include "_StopCondition.h"
#include "_BuilderSolution.h"
#include "_LocalSearch.h"

template  <class R, class V> class _Grasp_omp : public _Grasp<R,V> {
public:
    
    _Grasp_omp( 
            unsigned numThreads,
            _BuilderSolution<R,V>* builderSolution, 
            _StopCondition<R,V>* stopCondition,
            _SolutionDisturber<R,V>* solutionDisturber,
            _LocalSearch<R,V>* localSearch,
            _SolutionComparator<R, V>* solutionComparator):
                        _Grasp<R,V>(
                            builderSolution, 
                            stopCondition,
                            solutionDisturber,
                            localSearch,
                            solutionComparator),
                        numThreads(numThreads){}
                            
    virtual ~_Grasp_omp(){}
    
    virtual _Solution<R, V>* solve(_Solution<R,V>* solution) {
        
        omp_set_num_threads(this->numThreads);
        int auxAmount = this->solutionDisturber->GetAmount();
        this->solutionDisturber->SetAmount(this->numThreads);
        
        auto ret = solution;
        
        int i = 0;
        
        while(!this->stopCondition->stop(ret)){
            
            auto dsVector // vetor de soluções perturbadas
                = this->solutionDisturber->solvev(ret);
            
            #pragma omp parallel// num_threads(this->numThreads)
            {
                
                int threadId = omp_get_thread_num();
            
                auto lsResult // solução da busca local
                    = this->localSearch->solve(dsVector->at(threadId)); 

                if(dsVector->at(threadId) != lsResult){
                    
                    delete dsVector->at(threadId);
                                        
                } 
                
                #pragma omp critical
                {    

                    if((*this->solutionComparator)(*lsResult, *ret)){

                        if(ret != solution){
                            delete ret;
                        }

                        ret = lsResult;

                    } else {
                        
                        delete lsResult;
                        
                    }
                    
                    std::cout << i++ << "(" << threadId<<"): " << ret->evaluate() << std::endl;
                
                }
               
            
            }
                
            delete dsVector;
            
        }
        
        this->solutionDisturber->SetAmount(auxAmount);
        
        return ret;
        
    }
    
    virtual _Solution<R, V>* solve(_Instance* instance) {

        auto solution = this->builderSolution->solve(instance);
        
        auto ret = this->solve(solution);
                
        if(ret != solution) delete solution;
        
        return ret;

    }
    
private:
    
    unsigned numThreads;
            
};

#endif /* _GRASP_OMP_H */

