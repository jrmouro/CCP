#ifndef _GRASP_OMP_H
#define _GRASP_OMP_H

#include <omp.h>
#include <iostream>
#include "_Grasp.h"
#include "_Solution_Comparator.h"
#include "_Solution_Disturber.h"
#include "_Stop_Condition.h"
#include "_Builder_Solution.h"
#include "_Local_Search.h"

template <class V>
class _Grasp_omp : public _Grasp<V>
{
public:
    _Grasp_omp(
        unsigned numThreads,
        _Stop_Condition<V> &stopCondition,
        _Solution_Disturber<V> &solutionDisturber,
        const _Local_Search<V> &localSearch,
        const _Solution_Comparator<V> &solutionComparator) : _Grasp<V>(stopCondition,
                                                                       solutionDisturber,
                                                                       localSearch,
                                                                       solutionComparator),
                                                             numThreads(numThreads)
    {

        this->solutionDisturber.SetAmount(numThreads);
    }

    _Grasp_omp(
        unsigned numThreads,
        unsigned seed,
        _Stop_Condition<V> &stopCondition,
        _Solution_Disturber<V> &solutionDisturber,
        const _Local_Search<V> &localSearch,
        const _Solution_Comparator<V> &solutionComparator) : numThreads(numThreads),
                                                             _Grasp<V>(
                                                                 seed,
                                                                 stopCondition,
                                                                 solutionDisturber,
                                                                 localSearch,
                                                                 solutionComparator)
    {

        this->solutionDisturber.SetAmount(numThreads);
    }

    _Grasp_omp(const _Grasp_omp<V> &other) : _Grasp<V>(other),
                                             numThreads(other.numThreads) {}

    virtual ~_Grasp_omp() {}

    virtual _Solution<V> *solve(const _Solution<V> &solution){

        //Obtem-se uma cópia da solução dada
        auto ret = solution.clone();

        int i = 0; // eliminar. Só para acompanhar o andamento.

        // Itera até satisfazer uma condição dada
        while (!this->stopCondition.stop(*ret)){

            // Obtem-se um vetor de ponteiros de soluções modificadas randomicamente
            auto solv = this->solutionDisturber.solvev(*ret);

            #pragma omp parallel num_threads(this->numThreads)
            {

                int threadId = omp_get_thread_num();

                // Pega o ponteiro da solução corresposdente à thread
                auto localSol = solv->at(threadId);

                // Obtem-se um novo ponteiro de solução mediante a busca local
                auto lsSol = this->localSearch.solve(*localSol);

                // libera memória 
                delete localSol;

                #pragma omp critical
                {

                    // Compara a qualidade da solução com a solução a ser retornada
                    if (this->solutionComparator(*lsSol, *ret)){

                        // libera memória
                        delete ret;

                        // subistitui a solução a ser retornada pela solução melhor
                        ret = lsSol;

                         // eliminar. Só para acompanhar o andamento.
                        std::cout << i++ << "(" << threadId << "): " << ret->evaluate() << std::endl;

                    }
                    else{

                        // libera memória
                        delete lsSol;
                    }
                }
            }

            // libera memória do vetor de soluções 
            delete solv;

        }

        return ret;

    }

    virtual _Grasp_omp *clone()
    {
        return new _Grasp_omp(*this);
    }

protected:
    unsigned numThreads = 1;
};

#endif /* _GRASP_OMP_H */
