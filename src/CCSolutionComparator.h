#ifndef CCSOLUTIONCOMPARATOR_H
#define CCSOLUTIONCOMPARATOR_H

#include "_Solution.h"
#include "CCSolution.h"

class CCSolutionComparator {
public:
    CCSolutionComparator():rate(1){}
    CCSolutionComparator(int rate):rate(rate){}
    virtual bool operator()(_Solution<int*,int>& s1, _Solution<int*,int>& s2) const{
        return s1.evaluate() - (rate * ((CCSolution&)s1).GetPenalty()) > s2.evaluate() - (rate * ((CCSolution&)s2).GetPenalty());
    }
    virtual ~CCSolutionComparator(){}
private:
    int rate;
};

#endif /* CCSOLUTIONCOMPARATOR_H */

