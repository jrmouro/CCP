#ifndef _DISTURB_H
#define _DISTURB_H

#include "_SolutionAlgorithm.h"

template <class R, class V> class _SolutionDisturber: public _SolutionAlgorithm<R, V>, public _SolutionsAlgorithm<R, V>{

    public:
    _SolutionDisturber(unsigned amount = 1):_SolutionAlgorithm<R, V>(), _SolutionsAlgorithm<R, V>(), amount(amount) {}
    _SolutionDisturber(int seed, unsigned amount = 1):_SolutionAlgorithm<R, V>(seed), _SolutionsAlgorithm<R, V>(), amount(amount) {}
    virtual ~_SolutionDisturber(){}
    
    virtual std::vector<_Solution<R, V>*>* solvev(_Solution<R,V>* solution){
        
        std::vector<_Solution<R, V>*>* ret = new std::vector<_Solution<R, V>*>(this->amount);
        
        for (int i = 0; i < amount; i++) {
            
            ret->push_back(this->solve(solution));

        }
        
        return ret;
        
    }
    
    int GetRandomValue(int offset, int range){
        return _SolutionAlgorithm<R,V>::GetRandomValue(offset, range);        
    }
    
    unsigned GetAmount() const {
        return amount;
    }

    void SetAmount(unsigned amount) {
        this->amount = amount;
    }
    
private:
    
    unsigned amount = 1;
    
};

#endif /* _DISTURB_H */

