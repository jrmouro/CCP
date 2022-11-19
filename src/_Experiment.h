#ifndef _EXPERIMENT_H
#define _EXPERIMENT_H

#include <math.h>
#include <functional>
#include <vector>
#include "_Estochastic_Algorithm.h"
#include "_Solution.h"

template <class V> class _Experiment : public _Estochastic_Algorithm{
public:
    
    class _Result{
                
    public:
        
        _Result(std::string experimentName) : experimentName(experimentName) { }

        void add(const _Solution<V>& solution, long long time){
            solutions.push_back(solution.clone());
            times.push_back(time);
        }
        
        void list(const std::function<void(const _Solution<V>&, long long, unsigned)>& functor)const{
            for (int i = 0; i < times.size(); i++)                
                functor(*solutions.at(i), times.at(i), times.size());
        }
        
        virtual ~_Result(){
        
            for (auto elem : solutions) {
                delete elem;
            }

        
        }
        
        friend std::ostream& operator<<(std::ostream& os, const _Experiment<V>::_Result& obj) {
            os << "RESULT" << std::endl;
            os << "Experiment: " << obj.experimentName << std::endl;
            os << "Total Solutions: " << obj.times.size() << std::endl;
            os << "Total time: " << totalTime(obj) << std::endl;
            os << "Average time: " << averageTime(obj) << std::endl;
            os << "Sigma time: " << sigmaTime(obj) << std::endl;
            return os;
        }

        
        friend long long totalTime(const _Experiment<V>::_Result& result){
            unsigned ret = 0;
            result.list([&ret](const _Solution<V>& solution, long long time, unsigned size){
                ret += time;
            });
            return ret;
        }
        
        friend float averageTime(const _Experiment<V>::_Result& result){
            long long ret = 0;
            unsigned z;
            result.list([&ret, &z](const _Solution<V>& solution, long long time, unsigned size){
                ret += time;
                z = size;
            });
            if(z == 0) return 0.0;
            return (float)ret/(float)z;
        }
        
        friend float sigmaTime(const _Experiment<V>::_Result& result){
            float m = averageTime(result);
            float v = 0;
            unsigned z;
            result.list([&v, &z, m](const _Solution<V>& solution, long long time, unsigned size){
                float aux = (m -(float)time);
                v += aux * aux;
                z = size;
            });
            if(z < 2) return 0.0;
            return sqrt(v)/(float)(z-1);
        }
        
        private:
            
            std::vector<_Solution<V>*> solutions;
            std::vector<long long> times;
            std::string experimentName;
            
    };
    
    _Experiment(std::string name, unsigned repeat) : _Estochastic_Algorithm(), name(name), repeat(repeat){ }
    _Experiment(std::string name, unsigned repeat, unsigned seed) : _Estochastic_Algorithm(seed), name(name), repeat(repeat) {}
    _Experiment(const _Experiment<V>& other) : _Estochastic_Algorithm(other), name(other.name), repeat(other.repeat) {}
    
   virtual ~_Experiment(){}
   
   virtual _Experiment<V>::_Result* exec(){
       
       _Experiment<V>::_Result *ret = new _Experiment<V>::_Result(name);
       
        for (int i = 0; i < repeat; i++) {
           
            auto inicio = std::chrono::high_resolution_clock::now();
            auto solution = this->solve();
            auto resultado = std::chrono::high_resolution_clock::now() - inicio;
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(resultado).count();
            ret->add(*this->solve(), microseconds);
            
        }

       return ret;
       
   }
   
   virtual _Solution<V>* solve() = 0;
   
private:
   
   unsigned repeat;
   std::string name;
      
};

#endif /* _EXPERIMENT_H */

