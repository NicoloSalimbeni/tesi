#ifndef ObjAnColl_h
#define ObjAnColl_h

#include "ObjAnAbs.h"

class Visitor;

class ObjAnColl : public ObjAnAbs
{
public:
    ObjAnColl();
    virtual ~ObjAnColl();

    virtual void ComputeSolutions() override;
    virtual void Accept(Visitor *v) override;
    virtual void PrintFinalStats() override;

private:
};

#endif