#ifndef ViPrint_h
#define ViPrint_h
#include "TCanvas.h"
#include "../AnalysisFramework/Visitor.h"

class ViPrint : public Visitor
{
public:
    ViPrint();
    ~ViPrint();
    void Visit(ObjColl *) override;
    void Visit(ObjImpColl *) override;
    void Visit(ObjNonColl *) override;
    void Visit(ObjAnEs *) override;
    void Visit(ObjAnColl *) override;

private:
    TCanvas *c;
};

#endif