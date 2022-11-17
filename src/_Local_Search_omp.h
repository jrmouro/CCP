#ifndef _LOCAL_SEARCH_OMP_H
#define _LOCAL_SEARCH_OMP_H

#include <omp.h>
#include <vector>
#include "_Local_Search.h"
#include "_Solution.h"
#include "_Solution_Comparator.h"
#include "_Neighborhood_Algorithm.h"

template <class V> class _Local_Search_omp : public _Local_Search<V> {
public:

    _Local_Search_omp(
            unsigned numThreads,
            const _Neighborhood_Algorithm<V>& neighborhood,
            const _Solution_Comparator<V>& solutionComparator) :
                _Local_Search<V>(neighborhood, solutionComparator),
                numThreads(numThreads){}
                
    _Local_Search_omp(const _Local_Search_omp<V>& other) :
            numThreads(other.numThreads),
            _Local_Search<V>(other){ }

                
    virtual ~_Local_Search_omp() { }

    virtual _Solution<V>* solve(const _Solution<V>& solution) const {
        
        _Solution<V>* ret = solution.clone();
        
        #pragma omp parallel num_threads(this->numThreads)
        {
            int i = 1;
            
            int threadId = omp_get_thread_num();
            
            _Solution<V>* local = ret->clone();
        
            bool flag = true;
        
            while(flag){

                auto neighborhood = this->neighborhoodAlgorithm.solvev(*local);

                flag = false;

                for (auto neighbor : *neighborhood) {
                    
                    if (this->solutionComparator(*neighbor, *local)) {  
                        
                        delete local;
                        
                        local = neighbor;

                        flag = true;
                        
                        #pragma omp critical
                        {
                        
                            if (this->solutionComparator(*local, *ret)) {                                               

                                    delete ret;

                                    ret = local->clone();  

                                  std::cout << i++ << "(" << threadId<< "): " << ret->GetEvaluation() << std::endl; // eliminar

                            } else {

                                delete local;

                                local = ret->clone();

                            }
                        
                        }
                        
                    }else{
                        
                        delete neighbor;
                        
                    }
                    
                }

                delete neighborhood;

            }
            
            delete local;
                   
        }

        return ret;

    }
    
    virtual _Local_Search_omp* clone(){
        return new _Local_Search_omp(*this);
    }

protected:
    unsigned numThreads = 1;
};

#endif /* _LOCAL_SEARCH_OMP_H */

