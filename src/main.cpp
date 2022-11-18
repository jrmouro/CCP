#include <cstdlib>
#include <iostream>

#include "../CCP/src/CCGraph.h"
#include "../CCP/src/CCInstance.h"
#include "../CCP/src/CCBuilderSolution.h"
#include "../CCP/src/CCLocalSearch.h"
#include "../CCP/src/CCLocalSearch_omp.h"
#include "../CCP/src/CCNeighborhood.h"
#include "../CCP/src/CCSolutionComparator.h"
#include "../CCP/src/CCSolutionDisturber.h"
#include "../CCP/src/CCGrasp.h"
#include "../CCP/src/CCGrasp_omp.h"
#include "../CCP/src/CCStopCondition_Threshold.h"
#include "../CCP/src/_Experiment.h"

#define SEED 313131

int main(int argc, char** argv) {
    
    CCInstance i("RanReal240_01.txt"); 
//    std::cout << i << std::endl;
    CCSolutionComparator sc(10.0);
    CCNeighborhood ne;
    CCBuilderSolution bs;
    CCLocalSearch ls(ne, sc);
    CCLocalSearch_omp lsomp(8, ne, sc);
    CCSolutionDisturber sd(.2, .01, 1, SEED);
    CCStopCondition_Threshold stc(150000.0, 1000);
    CCGrasp g(SEED, bs, stc,  sd, ls, sc);
    CCGrasp_omp gomp(4, SEED, bs, stc,  sd, ls, sc);
    
     auto s = bs.solve(i);    
    std::cout << *(CCSolution*)s << std::endl;
//    auto sg = g.solve(*s);
    auto sg = gomp.solve(*s);
    std::cout << *(CCSolution*)sg << std::endl;
    
    delete sg;
    delete s;
    return 0;
}
