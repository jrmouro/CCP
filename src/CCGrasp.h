#ifndef _GRASP_H
#define _GRASP_H

template  <class R, class V> class _Grasp : public _InstanceAlgorithm<R,V> {
public:
    _Grasp( const _Greedy<R,V>& greedy, 
            const _StopCondition<R,V>& stopCondition,
            const _SolutionDisturber<R,V>& solutionDisturber,
            const _LocalSearch<R,V>& localSearch,
            const _SolutionComparator<_Solution<R, V>>& comparator):
                        greedy(greedy),
                        stopCondition(stopCondition),
                        solutionDisturber(solutionDisturber),
                        localSearch(localSearch),
                        comparator(comparator){}
                        
    _Grasp(const _Grasp& orig):
                        greedy(orig.greedy),
                        stopCondition(orig.stopCondition),
                        solutionDisturber(orig.solutionDisturber),
                        localSearch(orig.localSearch),
                        comparator(orig.comparator){}
    
    virtual ~_Grasp(){}
    
    virtual _Solution<R, V> solve(const _Instance& instance) {

        auto solution = this->greedy.solve(instance);
        
        while(!this->stopCondition.stop(solution)){
            
            auto aux = this->solutionDisturber.solve(solution);
            
            aux = this->localSearch.solve(aux);                       
            
            if(this->comparator(aux, solution)){
                
                solution = aux;
                
            }
            
        }
        
        return solution;

    }
    
private:
    _Greedy<R,V> greedy;
    _SolutionDisturber<R,V> solutionDisturber;
    _SolutionComparator<_Solution<R, V>> comparator;
    _StopCondition<R,V> stopCondition;
    _LocalSearch<R,V> localSearch;
            
};

#endif /* _GRASP_H */

