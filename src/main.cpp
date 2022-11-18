#include <cstdlib>
#include <iostream>

#include "../CCP2/src/CCGraph.h"
#include "../CCP2/src/CCInstance.h"
#include "../CCP2/src/CCBuilderSolution.h"
#include "../CCP2/src/CCLocalSearch.h"
#include "../CCP2/src/CCLocalSearch_omp.h"
#include "../CCP2/src/CCNeighborhood.h"
#include "../CCP2/src/CCSolutionComparator.h"
#include "../CCP2/src/CCSolutionDisturber.h"
#include "../CCP2/src/CCGrasp.h"
#include "../CCP2/src/CCGrasp_omp.h"
#include "../CCP2/src/CCStopCondition_Threshold.h"

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
//    CCGrasp g2(SEED, bs, stc,  sd, lsomp, sc);
    CCGrasp_omp gomp(4, SEED, bs, stc,  sd, ls, sc);
    
    auto s = bs.solve(i);
//    auto sls = ls.solve(*s);
//    auto sls = lsomp.solve(*s);
    auto sg = g.solve(*s);
//    auto sg = gomp.solve(*s);
    
    std::cout << *(CCSolution*)s << std::endl;
//    std::cout << *(CCSolution*)ds << std::endl;
//    std::cout << *(CCSolution*)sls << std::endl;
    std::cout << *(CCSolution*)sg << std::endl;
    
    delete sg;
//    delete sls;
//    delete ds;
    delete s;
    return 0;
}

