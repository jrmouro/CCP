#ifndef _ESTOCHASTIC_SOLUTIONS_ALGORITHM_H
#define _ESTOCHASTIC_SOLUTIONS_ALGORITHM_H

#include <vector>
#include "_Estochastic_Solution_Algorithm.h"
#include "_Solution.h"

template <class V> class _Estochastic_Solutions_Algorithm : public _Estochastic_Solution_Algorithm<V> {
public:
    _Estochastic_Solutions_Algorithm(unsigned amount):_Estochastic_Solution_Algorithm<V>(), amount(amount) {}
    _Estochastic_Solutions_Algorithm(unsigned amount, unsigned seed):_Estochastic_Solution_Algorithm<V>(seed), amount(amount) {}
    _Estochastic_Solutions_Algorithm(const _Estochastic_Solutions_Algorithm<V>& other) :
            _Estochastic_Solution_Algorithm<V>(other),
            amount(other.amount) { }
    virtual ~_Estochastic_Solutions_Algorithm() {}
    
    
    virtual std::vector<_Solution<V>*>* solvev(const _Solution<V>& solution) {
        auto ret = new std::vector<_Solution<V>*>();
        for(int i = 0; i < this->amount; i++)
            ret->push_back(this->solve(solution));
        return ret;
    }
    
    unsigned GetAmount() const {
        return amount;
    }

    void SetAmount(unsigned amount) {
        this->amount = amount;
    }

    private:
        unsigned amount;
};

#endif /* _ESTOCHASTIC_SOLUTIONS_ALGORITHM_H */

