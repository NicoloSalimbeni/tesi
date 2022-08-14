#ifndef ObjAnColl_h
#define ObjAnColl_h

#include "ObjAnAbs.h"

class Visitor;

class ObjAnColl : public ObjAnAbs
{
public:
    ObjAnColl();
    virtual ~ObjAnColl();

    virtual void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) override;
    virtual void Accept(Visitor *v) override;

private:
};

#endif