#ifndef _EVALUABLE_H
#define _EVALUABLE_H

template <class V>
class _Evaluable {
public:
    _Evaluable(){}
    _Evaluable(const V& evaluation):
        evaluation(evaluation), 
        _isEvaluated(true){}
    _Evaluable(const _Evaluable<V>& other) :
        evaluation(other.evaluation), 
        _isEvaluated(other._isEvaluated) { }
    _Evaluable(_Evaluable<V>* other) :
        evaluation(other->evaluation), 
        _isEvaluated(other-_isEvaluated) { }
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
    
    V GetEvaluation() const {
        return evaluation;
    }

protected:
    virtual V reevaluate() = 0;
    V evaluation;
    bool _isEvaluated = false;
};

#endif /* _EVALUABLE_H */

