#include "../AnalysisObjects/ObjColl.h"
#include "../AnalysisObjects/ObjImpColl.h"
#include "../AnalysisObjects/ObjNonColl.h"
#include "../AnalysisObjects/ObjAn.h"
#include "../AnalysisObjects/ObjAnColl.h"
#include "ViSave.h"

ViSave::ViSave()
{
}

ViSave::~ViSave()
{
    delete f;
}

void ViSave::Visit(ObjColl *obj)
{
    f = new TFile("../grafici.root", "UPDATE");
    f->cd();

    f->Delete("Resolution_coll;*");
    f->Delete("Profile_coll;*");
    obj->GetH()->Write();
    obj->GetP()->Write();

    f->Close();
}

void ViSave::Visit(ObjImpColl *obj)
{
    f = new TFile("../grafici.root", "UPDATE");
    f->cd();

    f->Delete("Resolution_imp_coll;*");
    f->Delete("Profile_imp_coll;*");
    obj->GetH()->Write();
    obj->GetP()->Write();

    f->Close();
}

void ViSave::Visit(ObjNonColl *obj)
{
    f = new TFile("../grafici.root", "UPDATE");
    f->cd();

    f->Delete("Resolution_non_coll;*");
    f->Delete("Profile_non_coll;*");
    obj->GetH()->Write();
    obj->GetP()->Write();

    f->Close();
}

void ViSave::Visit(ObjAn *obj)
{
    f = new TFile("../grafici.root", "UPDATE");
    f->cd();

    f->Delete("Resolution_an_mag;*");
    f->Delete("Resolution_an_min;*");
    f->Delete("Resolution_an_cos;*");
    f->Delete("Profile_an_corr;*");
    f->Delete("Profile_an_mean;*");
    f->Delete("Profile_an_cos;*");
    obj->GetHMag()->Write();
    obj->GetHMin()->Write();
    obj->GetHMean()->Write();
    obj->GetHCos()->Write();
    obj->GetHCorr()->Write();

    obj->GetPMean()->Write();
    obj->GetPCos()->Write();
    obj->GetPCorr()->Write();

    f->Close();
}

void ViSave::Visit(ObjAnColl *obj) {} // TODO
