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
    virtual ~_Evaluable() {}
    virtual bool isEvaluated() {return this->_isEvaluated;}
    
    virtual V evaluate()final{ 
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
    
    void SetIsEvaluated(bool _isEvaluated) {
        this->_isEvaluated = _isEvaluated;
    }

    void SetEvaluation(V evaluation) {
        this->evaluation = evaluation;
    }

    virtual V reevaluate() = 0;
    
    virtual _Evaluable<V>* clone() const = 0;

private:
    
    V evaluation;
    bool _isEvaluated = false;
    
};

#endif /* _EVALUABLE_H */

