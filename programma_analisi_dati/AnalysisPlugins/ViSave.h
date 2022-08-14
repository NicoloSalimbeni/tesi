#ifndef ViSave_h
#define ViSave_h
#include "TFile.h"
#include "../AnalysisFramework/Visitor.h"

class ViSave : public Visitor
{
public:
    ViSave();
    ~ViSave();
    void Visit(ObjColl *) override;
    void Visit(ObjImpColl *) override;
    void Visit(ObjNonColl *) override;
    void Visit(ObjAnEs *) override;
    void Visit(ObjAnColl *) override;

private:
    TFile *f;
};

#endif