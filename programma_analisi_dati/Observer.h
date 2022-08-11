#ifndef Observer_h
#define Observer_h
#include "TLorentzVector.h"

class Observer
{
public:
    Observer();
    virtual ~Observer();
    virtual void Update(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) = 0;
};

#endif