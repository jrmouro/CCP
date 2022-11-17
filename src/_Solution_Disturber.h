#ifndef _SOLUTION_DISTURB_H
#define _SOLUTION_DISTURB_H

#include "_Estochastic_Solutions_Algorithm.h"

template <class V> class _Solution_Disturber: public _Estochastic_Solutions_Algorithm<V>{

public:
    _Solution_Disturber(unsigned amount):
                _Estochastic_Solutions_Algorithm<V>(amount){}
                
    _Solution_Disturber(int seed, unsigned amount):
                _Estochastic_Solutions_Algorithm<V>(seed, amount){}
    
    _Solution_Disturber(const _Solution_Disturber<V>& other) :
    _Estochastic_Solutions_Algorithm<V>(other) { }
        
    virtual ~_Solution_Disturber(){}
    
    
};

#endif /* _SOLUTION_DISTURB_H */

