#ifndef CCEXPERIMENT_H
#define CCEXPERIMENT_H

#include "_Experiment.h"
#include "_Solution_Algorithm.h"

class CCExperiment : public _Experiment<float>{
public:
        
    CCExperiment(
            _Solution_Algorithm<float>& algorithm,
            const CCSolution& initialSolution,
            std::string name,
            unsigned repeat) : 
                    _Experiment<float>(name, repeat), 
                        algorithm(algorithm), 
                        initialSolution(initialSolution){ }
                            
    CCExperiment(const CCExperiment& other) :
                    _Experiment<float>(other), 
                        algorithm(other.algorithm), 
                        initialSolution(other.initialSolution){}
    
   virtual ~CCExperiment(){}
   
   virtual _Experiment<float>::_Result* exec(){
       algorithm.reset();
       return _Experiment<float>::exec();
   }
      
   virtual _Solution<float>* solve(){       
       return algorithm.solve(initialSolution);
   }
   
   virtual CCExperiment* clone(){
       return new CCExperiment(*this);
   }
   
private:
    _Solution_Algorithm<float>& algorithm;
    const CCSolution& initialSolution;
      
};

#endif /* CCEXPERIMENT_H */

