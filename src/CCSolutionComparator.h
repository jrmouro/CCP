#ifndef CCSOLUTIONCOMPARATOR_H
#define CCSOLUTIONCOMPARATOR_H

#include "_Solution.h"
#include "CCSolution.h"

class CCSolutionComparator {
public:
    CCSolutionComparator():rate(1.0){}
    CCSolutionComparator(float rate):rate(rate){}
    virtual bool operator()(_Solution<int*,float>& s1, _Solution<int*,float>& s2) const{
        return s1.evaluate() - s1.evaluate()* rate * ((CCSolution&)s1).GetPenalty() > s2.evaluate() - s2.evaluate() * rate * ((CCSolution&)s2).GetPenalty();
    }
    virtual ~CCSolutionComparator(){}
private:
    float rate;
};

#endif /* CCSOLUTIONCOMPARATOR_H */

