#ifndef _SOLUTION_DISTURB_H
#define _SOLUTION_DISTURB_H

#include "_Solutions_Algorithm.h"
#include "_Estochastic.h"

template <class V> class _Solution_Disturber: public _Solutions_Algorithm<V>{

public:
    _Solution_Disturber(
            _Estochastic& estochastic,
            unsigned amount):
                _Solutions_Algorithm<V>(), estochastic(estochastic), amount(amount){}
                    
    _Solution_Disturber(const _Solution_Disturber<V>& other) :
    _Solutions_Algorithm<V>(other), amount(other.amount), estochastic(other.estochastic) { }
        
    virtual ~_Solution_Disturber(){}
    
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
    
    _Estochastic& GetEstochastic() const {
        return estochastic;
    }
    
    virtual void reset(){
        estochastic.reset();
    }
    
    private:
        unsigned amount;
        _Estochastic& estochastic;
        
};

#endif /* _SOLUTION_DISTURB_H */

