#ifndef CCSOLUTIONCOMPARATOR_H
#define CCSOLUTIONCOMPARATOR_H

#include "_Solution.h"
#include "_Solution_Comparator.h"
#include "CCSolution.h"

class CCSolutionComparator:public _Solution_Comparator<float> {

public:

    CCSolutionComparator():rate(1.0){}
    CCSolutionComparator(float rate):rate(rate){}
    CCSolutionComparator(const CCSolutionComparator& other):rate(other.rate){}

    virtual bool operator()(const _Solution<float>& s1, const _Solution<float>& s2) const{
        return s1.GetEvaluation() - s1.GetEvaluation()* rate * ((CCSolution&)s1).GetPenalty() > s2.GetEvaluation() - s2.GetEvaluation() * rate * ((CCSolution&)s2).GetPenalty();
    }
    
    virtual bool operator()(const _Solution<float>& solution, const float& value) const{
        return solution.GetEvaluation() - solution.GetEvaluation()* rate * ((CCSolution&)solution).GetPenalty() > value;
    }    
   
    
    virtual ~CCSolutionComparator(){}
    
    virtual CCSolutionComparator* clone(){
        return new CCSolutionComparator(*this);
    }
    
private:
    float rate;
};

#endif /* CCSOLUTIONCOMPARATOR_H */

