#include <cstdlib>
#include <iostream>
#include "./src/CCGraph.h"
#include "./src/CCCluster.h"
#include "./src/CCInstance.h"
#include "./src/CCBuilderSolution.h"
#include "./src/CCNeighborhood.h"
#include "./src/_LocalSearch.h"
#include "./src/CCSolutionComparator.h"
#include "./src/CCLocalSearch.h"
#include "./src/CCSolutionDisturber.h"
#include "./src/CCGrasp.h"
#include "./src/CCStopCondition.h"

int main(int argc, char** argv) {
    
    CCInstance i("RanReal240_01.txt");
//    std::cout << "Instance:" << std::endl << i << std::endl;
    
    CCBuilderSolution bs;
    CCSolution *s = (CCSolution*)bs.solve(&i);
    s->evaluate();
    std::cout << "Initial Solution: "<< std::endl << *s << std::endl;
        
    CCNeighborhood neig;
    CCSolutionComparator sc(5.0);
    CCSolutionDisturber sd(.5);    
    CCLocalSearch ls(&neig, &sc);
    CCStopCondition xc(220000.f, 0.90f);
    CCGrasp gr(&bs, &xc, &sd, &ls, &sc);
    
    CCSolution *ss = (CCSolution*)gr.solve(&i);
    std::cout << "Grasp Solution: "<< std::endl << *ss << std::endl;
    
   
    
    delete s;
    delete ss;

    return 0;
}

