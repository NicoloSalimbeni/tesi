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
    f->Delete("Hist_residui_Coll;*");
    obj->GetH()->Write();
    obj->GetP()->Write();
    obj->GetHResidui()->Write();
    f->Close();

    std::cout << "ObjColl saved in grafici.root" << std::endl;
}

void ViSave::Visit(ObjImpColl *obj)
{
    f = new TFile("../grafici.root", "UPDATE");
    f->cd();

    f->Delete("Resolution_imp_coll;*");
    f->Delete("Profile_imp_coll;*");
    f->Delete("Hist_residui_ImpColl;*");
    obj->GetH()->Write();
    obj->GetP()->Write();
    obj->GetHResidui()->Write();

    f->Close();

    std::cout << "ObjImpColl saved in grafici.root" << std::endl;
}

void ViSave::Visit(ObjNonColl *obj)
{
    f = new TFile("../grafici.root", "UPDATE");
    f->cd();

    f->Delete("Resolution_non_coll;*");
    f->Delete("Profile_non_coll;*");
    f->Delete("Hist_residui_NonColl;*");
    obj->GetH()->Write();
    obj->GetP()->Write();
    obj->GetHResidui()->Write();

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
    f->Delete("Resolution_anEs_collcomp;*");
    f->Delete("Resolution_anEs_random;*");
    obj->GetHMag()->Write();
    obj->GetHMin()->Write();
    obj->GetHMean()->Write();
    obj->GetHCos()->Write();
    obj->GetHCorr()->Write();
    obj->GetHCollComp()->Write();
    obj->GetHRandom()->Write();

    f->Delete("Hist_residui_AnEs_mag;*");
    f->Delete("Hist_residui_AnEs_min;*");
    f->Delete("Hist_residui_AnEs_mean;*");
    f->Delete("Hist_residui_AnEs_cos;*");
    f->Delete("Hist_residui_AnEs_corr;*");
    f->Delete("Hist_residui_AnEs_collcomp;*");
    f->Delete("Hist_residui_AnEs_random;*");
    obj->GetHResiduiMin()->Write();
    obj->GetHResiduiMag()->Write();
    obj->GetHResiduiCorr()->Write();
    obj->GetHResiduiMean()->Write();
    obj->GetHResiduiCos()->Write();
    obj->GetHResiduiCollComp()->Write();
    obj->GetHResiduiRandom()->Write();

    f->Delete("Profile_anEs_corr;*");
    f->Delete("Profile_anEs_mean;*");
    f->Delete("Profile_anEs_cos;*");
    f->Delete("Profile_anEs_collcomp;*");
    f->Delete("Profile_anEs_random;*");
    obj->GetPMean()->Write();
    obj->GetPCos()->Write();
    obj->GetPCorr()->Write();
    obj->GetPCollComp()->Write();
    obj->GetPRandom()->Write();

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
    f->Delete("Resolution_anColl_collcomp;*");
    obj->GetHMag()->Write();
    obj->GetHMin()->Write();
    obj->GetHMean()->Write();
    obj->GetHCos()->Write();
    obj->GetHCorr()->Write();
    obj->GetHCollComp()->Write();

    f->Delete("Hist_residui_AnColl_mag;*");
    f->Delete("Hist_residui_AnColl_min;*");
    f->Delete("Hist_residui_AnColl_mean;*");
    f->Delete("Hist_residui_AnColl_cos;*");
    f->Delete("Hist_residui_AnColl_corr;*");
    f->Delete("Hist_residui_AnColl_collcomp;*");
    obj->GetHResiduiMin()->Write();
    obj->GetHResiduiMag()->Write();
    obj->GetHResiduiCorr()->Write();
    obj->GetHResiduiMean()->Write();
    obj->GetHResiduiCos()->Write();
    obj->GetHResiduiCollComp()->Write();

    f->Delete("Profile_anColl_corr;*");
    f->Delete("Profile_anColl_mean;*");
    f->Delete("Profile_anColl_cos;*");
    f->Delete("Profile_anColl_collcomp;*");
    obj->GetPMean()->Write();
    obj->GetPCos()->Write();
    obj->GetPCorr()->Write();
    obj->GetPCollComp()->Write();

    f->Close();

    std::cout << "ObjAnColl saved in grafici.root" << std::endl;
}
