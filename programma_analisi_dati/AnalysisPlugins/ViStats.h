#ifndef ViStats_h
#define ViStats_h
#include "TFile.h"
#include "../AnalysisFramework/Visitor.h"

class ViStats : public Visitor
{
public:
    ViStats();
    ~ViStats();
    void Visit(ObjColl *) override;
    void Visit(ObjImpColl *) override;
    void Visit(ObjNonColl *) override;
    void Visit(ObjAnEs *) override;
    void Visit(ObjAnColl *) override;

private:
};

#endif