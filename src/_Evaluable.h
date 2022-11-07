#ifndef _EVALUABLE_H
#define _EVALUABLE_H

template <class V>
class _Evaluable {
public:
    _Evaluable(){}
    _Evaluable(const V& evaluation):evaluation(evaluation), _isEvaluated(true){}
    virtual ~_Evaluable() {}
    virtual bool isEvaluated() {return this->_isEvaluated;}
    virtual V evaluate(){ 
        if(this->_isEvaluated) {
            return evaluation; 
        }else{ 
            evaluation = this->reevaluate();
            this->_isEvaluated = true;
            return evaluation;
        }
    }
    virtual V reevaluate() = 0;
protected:
    V evaluation;
    bool _isEvaluated = false;
};

#endif /* _EVALUABLE_H */

