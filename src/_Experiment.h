#ifndef _EXPERIMENT_H
#define _EXPERIMENT_H

#include <vector>
#include "_Clonable.h"
#include "_Resetable.h"

template <class V> class _Experiment : public _Algorithm{
public:
    
    class _Result{
                
    public:
        
        void add(const _Solution<V>& solution, unsigned time){
            solutions.push_back(solution);
            times.push_back(time);
            totalTime += time;
        }
        
        virtual ~_Result(){
        
            for (auto elem : solutions) {
                delete elem;
            }
        
        }
        
        private:
            
            std::vector<_Solution<V>> solutions;
            std::vector<unsigned> times;
            unsigned totalTime = 0;
            
    };
    
    
   virtual ~_Experiment(){}
   
   virtual _Experiment<V>::_Result solve(const _Instance& instance, const _Algorithm& algorithm) = 0;
   
};

#endif /* _EXPERIMENT_H */

