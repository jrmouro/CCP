#ifndef CCEXPERIMENT_H
#define CCEXPERIMENT_H

#include "_Experiment.h"
#include "_Estochastic_Solution_Algorithm.h"

class CCExperiment : public _Experiment<float>{
public:
        
    CCExperiment(
            _Estochastic_Solution_Algorithm<float>& algorithm,
            const CCSolution& initialSolution,
            std::string name,
            unsigned repeat) : 
                    _Experiment<float>(name, repeat), 
                        algorithm(algorithm), 
                        initialSolution(initialSolution){ }
                    
    CCExperiment(
            _Estochastic_Solution_Algorithm<float>& algorithm,
            const CCSolution& initialSolution,
            std::string name,
            unsigned repeat, 
            unsigned seed) :  
                    _Experiment<float>(name, repeat,seed), 
                        algorithm(algorithm), 
                        initialSolution(initialSolution){ }
    
    CCExperiment(const CCExperiment& other) :
                    _Experiment<float>(other), 
                        algorithm(other.algorithm), 
                        initialSolution(other.initialSolution){}
    
   virtual ~CCExperiment(){}
      
   virtual _Solution<float>* solve(){
       algorithm.SetSeed(this->GetSeed()); 
       return algorithm.solve(initialSolution);
   }
   
   virtual CCExperiment* clone(){
       return new CCExperiment(*this);
   }
   
private:
    _Estochastic_Solution_Algorithm<float>& algorithm;
    const CCSolution& initialSolution;
      
};

#endif /* CCEXPERIMENT_H */

