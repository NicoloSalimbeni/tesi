#ifndef ViFitProfile_h
#define ViFitProfile_h

#include "TFitResultPtr.h"
#include "../AnalysisFramework/Visitor.h"

class TFile;

class ViFitProfile : public Visitor
{
public:
    ViFitProfile();
    ~ViFitProfile();
    void Visit(ObjColl *) override;
    void Visit(ObjImpColl *) override;
    void Visit(ObjNonColl *) override;
    void Visit(ObjAn *) override;
    void Visit(ObjAnColl *) override;

private:
    TFile *f_ris_fit;
    TFitResultPtr risultati_fit;
};

#endif