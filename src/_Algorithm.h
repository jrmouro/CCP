#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include "_Clonable.h"
#include "_Resetable.h"

class _Algorithm : public _Clonable, public _Resetable{
public:
   virtual ~_Algorithm(){}
   virtual void reset(){}
};

#endif /* _ALGORITHM_H */

