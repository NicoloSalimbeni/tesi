#ifndef ObjAnEs_h
#define ObjAnEs_h

#include "ObjAnAbs.h"

class Visitor;

class ObjAnEs : public ObjAnAbs
{
public:
    ObjAnEs();
    virtual ~ObjAnEs();

    virtual void ComputeSolutions() override;
    virtual void Accept(Visitor *v) override;
    virtual void PrintFinalStats() override;

private:
};

#endif