#include "../AnalysisObjects/ObjColl.h"
#include "../AnalysisObjects/ObjImpColl.h"
#include "../AnalysisObjects/ObjNonColl.h"
#include "../AnalysisObjects/ObjAnEs.h"
#include "../AnalysisObjects/ObjAnColl.h"
#include "ViSave.h"

#include <iostream>

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

    std::cout << "ObjColl saved in grafici.root" << std::endl;
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

    std::cout << "ObjImpColl saved in grafici.root" << std::endl;
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

    std::cout << "ObjNonColl saved in grafici.root" << std::endl;
}

void ViSave::Visit(ObjAnEs *obj)
{
    f = new TFile("../grafici.root", "UPDATE");
    f->cd();

    f->Delete("Resolution_anEs_mag;*");
    f->Delete("Resolution_anEs_min;*");
    f->Delete("Resolution_anEs_cos;*");
    f->Delete("Resolution_anEs_mean;*");
    f->Delete("Resolution_anEs_corr;*");
    f->Delete("Profile_anEs_corr;*");
    f->Delete("Profile_anEs_mean;*");
    f->Delete("Profile_anEs_cos;*");
    obj->GetHMag()->Write();
    obj->GetHMin()->Write();
    obj->GetHMean()->Write();
    obj->GetHCos()->Write();
    obj->GetHCorr()->Write();

    obj->GetPMean()->Write();
    obj->GetPCos()->Write();
    obj->GetPCorr()->Write();

    f->Close();

    std::cout << "ObjAnEs saved in grafici.root" << std::endl;
}

void ViSave::Visit(ObjAnColl *obj)
{
    f = new TFile("../grafici.root", "UPDATE");
    f->cd();

    f->Delete("Resolution_anColl_mag;*");
    f->Delete("Resolution_anColl_min;*");
    f->Delete("Resolution_anColl_cos;*");
    f->Delete("Resolution_anColl_mean;*");
    f->Delete("Resolution_anColl_corr;*");
    f->Delete("Profile_anColl_corr;*");
    f->Delete("Profile_anColl_mean;*");
    f->Delete("Profile_anColl_cos;*");
    obj->GetHMag()->Write();
    obj->GetHMin()->Write();
    obj->GetHMean()->Write();
    obj->GetHCos()->Write();
    obj->GetHCorr()->Write();

    obj->GetPMean()->Write();
    obj->GetPCos()->Write();
    obj->GetPCorr()->Write();

    f->Close();

    std::cout << "ObjAnColl saved in grafici.root" << std::endl;
}
