#ifndef CCNEIGHBORHOOD_OMP_H
#define CCNEIGHBORHOOD_OMP_H

#include <omp.h>
#include <vector>
#include <iostream>
#include "_Neighborhood_Algorithm.h"
#include "_Solution.h"
#include "CCSolution.h"

class CCNeighborhood_omp : public CCNeighborhood {
public:

    CCNeighborhood_omp(const _Solution_Comparator<float>& solutionComparator, unsigned numThreads) : CCNeighborhood(solutionComparator), numThreads(numThreads) {
    }

    CCNeighborhood_omp(const CCNeighborhood_omp& other) : CCNeighborhood(other), numThreads(other.numThreads) {
    }

    virtual ~CCNeighborhood_omp() {
    }

    virtual std::vector<_Solution<float>*>* solvev(const _Solution<float>& solution) {

        int nClusters = ((const CCSolution&) solution).GetInstance().GetNClusters();
        int size = ((const CCSolution&) solution).GetInstance().GetSize();

        std::vector<_Solution<float>*>* ret = new std::vector<_Solution<float>*>();
        ret->reserve(size * nClusters * nClusters);

        #pragma omp parallel num_threads(this->numThreads)
        {

            int threadId = omp_get_thread_num();

            int _size = size / this->numThreads;

            int aux = threadId * _size + _size;

            for (int n = threadId * _size; n < aux; n++) {

                for (int i = 0; i < nClusters - 1; i++) {

                    for (int j = 0; j < nClusters; j++) {

                        auto s = (CCSolution*) solution.clone();

                        float aux = s->SwapNodo(n, i, j);

                        if (aux > 0.0) {

                            #pragma omp critical
                            {

                                ret->push_back(s);

                            }

                        } else {

                            delete s;

                        }

                    }
                }
            }
        }

        return ret;

    }

    virtual _Solution<float>* solve(const _Solution<float>& solution) {

        auto ret = solution.clone();

        int nClusters = ((const CCSolution&) solution).GetInstance().GetNClusters();
        int size = ((const CCSolution&) solution).GetInstance().GetSize();

        #pragma omp parallel num_threads(this->numThreads)
        {

            int threadId = omp_get_thread_num();

            int _size = size / this->numThreads;

            int aux = threadId * _size + _size;

            for (int n = threadId * _size; n < aux; n++) {

                for (int i = 0; i < nClusters - 1; i++) {

                    for (int j = 0; j < nClusters; j++) {

                        auto s = (CCSolution*) solution.clone();

                        float aux = s->SwapNodo(n, i, j);
                        
                        #pragma omp critical
                        {

                            if (this->solutionComparator(*s, *ret)) {

                                delete ret;
                                ret = s;

                            } else {

                                delete s;

                            }
                        
                        }
                    }
                }
            }
        }
        
        return ret;

    }

    virtual CCNeighborhood_omp* clone() {
        return new CCNeighborhood_omp(*this);
    }

private:
    unsigned numThreads;


};

#endif /* CCNEIGHBORHOOD_OMP_H */