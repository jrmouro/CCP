#ifndef CCNEIGHBORHOOD_OMP_H
#define CCNEIGHBORHOOD_OMP_H

#include <omp.h>
#include <vector>
#include <iostream>
#include "CCNeighborhood.h"
#include "CCSolutionComparator.h"
#include "_Solution.h"
#include "CCSolution.h"
#include <stdio.h>
#include <string.h>

__global__ void neighbor_cuda(
    
    const _Solution_Comparator<float>& solutionComparator, 
    int n_nodos, 
    int n_clusters){
    
    extern  __shared__ CCSolution* shared_sol;

    int n = n_nodos * n_clusters * n_clusters;
    
    int ti = threadIdx.x;
    int bd = blockDim.x;   
   
    for(int i = ti; i < n; i += bd){
        
        int nodo = i / n_clusters / n_clusters;
        int rest = i - nodo;
        int c1 = rest / n_clusters;
        int c2 = rest % n_clusters;

        CCSolution* sol_aux = (CCSolution*) malloc(sizeof(CCSolution));
        
        memcpy(sol_aux, shared_sol, sizeof(CCSolution));

        float aux = sol_aux->SwapNodo(nodo, c1, c1);
        
        if (aux > 0.0) {
            
            __syncthreads();

            if (solutionComparator.compare(*sol_aux, *shared_sol)) {

                memcpy(shared_sol, sol_aux, sizeof(CCSolution));                

            } 

        } 
        
        free(sol_aux);
        
    }

}

class CCNeighborhood_cuda : public CCNeighborhood {
public:

    CCNeighborhood_cuda(
        const _Solution_Comparator<float>& solutionComparator, 
        unsigned numThreads) : 
            CCNeighborhood(solutionComparator), 
            numThreads(numThreads) { }

    CCNeighborhood_cuda(
        const CCNeighborhood_cuda& other) : 
            CCNeighborhood(other), 
            numThreads(other.numThreads) { }

    virtual ~CCNeighborhood_cuda() { }

    virtual std::vector<_Solution<float>*>* solvev(const _Solution<float>& solution) {

        int nClusters = ((const CCSolution&) solution).GetInstance().GetNClusters();
        int size = ((const CCSolution&) solution).GetInstance().GetSize();

        std::vector<_Solution<float>*>* ret = new std::vector<_Solution<float>*>();
        ret->reserve(size * nClusters * nClusters);

        ret->push_back(this->solve(solution));

        return ret;

    }

    virtual _Solution<float>* solve(const _Solution<float>& solution) {

        _Solution<float>* ret;

        int n_Clusters = ((const CCSolution&) solution).GetInstance().GetNClusters();
        int n_nodos = ((const CCSolution&) solution).GetInstance().GetSize();
                
        CCSolution *sol_cuda;
        
        cudaMalloc((void **)&sol_cuda, sizeof(CCSolution));
        
        cudaMemcpy(sol_cuda, &((const CCSolution&) solution), sizeof(CCSolution), cudaMemcpyHostToDevice);
        
        neighbor_cuda<<<1, this->numThreads, sizeof(CCSolution)>>>(this->solutionComparator, n_nodos, n_Clusters);
         
        cudaMemcpy(ret, sol_cuda, sizeof(CCSolution), cudaMemcpyDeviceToHost);
        
        cudaFree(sol_cuda);
                       
        return ret;

    }

    virtual CCNeighborhood_cuda* clone() {
        return new CCNeighborhood_cuda(*this);
    }

private:
    unsigned numThreads;

};

#endif /* CCNEIGHBORHOOD_OMP_H */