#ifndef _EVALUABLE_H
#define _EVALUABLE_H

template <class V>
class _Evaluable {
public:
    _Evaluable(){}
    _Evaluable(const V& evaluation):evaluation(evaluation), isEvaluation(true){}
    virtual ~_Evaluable() {}
    virtual bool isEvaluate() {return this->isEvaluation;}
    virtual V evaluate(){ if(this->isEvaluation) return evaluation; else return this->reevaluate();}
    virtual V reevaluate() = 0;
private:
    V evaluation;
    bool isEvaluation = false;
};

#endif /* _EVALUABLE_H */

