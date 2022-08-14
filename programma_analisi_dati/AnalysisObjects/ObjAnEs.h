#ifndef ObjAnEs_h
#define ObjAnEs_h

#include "ObjAnAbs.h"

class Visitor;

class ObjAnEs : public ObjAnAbs
{
public:
    ObjAnEs();
    virtual ~ObjAnEs();

    virtual void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) override;
    virtual void Accept(Visitor *v) override;

private:
};

#endif