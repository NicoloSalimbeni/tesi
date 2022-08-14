#include "../AnalysisObjects/ObjColl.h"
#include "../AnalysisObjects/ObjImpColl.h"
#include "../AnalysisObjects/ObjNonColl.h"
#include "../AnalysisObjects/ObjAn.h"
#include "../AnalysisObjects/ObjAnColl.h"

#include "TFitResult.h"
#include "ViFitProfile.h"
#include "TFile.h"

#include <iostream>

ViFitProfile::ViFitProfile()
{
}

ViFitProfile::~ViFitProfile()
{
}

void ViFitProfile::Visit(ObjColl *obj)
{
    f_ris_fit = new TFile("../analisi_risoluzione_energia/risultati_fit_profile.root", "UPDATE");
    f_ris_fit->cd();

    f_ris_fit->Delete("fit_res_coll;*");

    risultati_fit = obj->GetP()->Fit(obj->GetF(), "SR");
    risultati_fit->SetNameTitle("fit_res_coll", "pol4");
    risultati_fit->Write();

    f_ris_fit->Close();

    std::cout << "fit ObjColl eseguito" << std::endl;
}

void ViFitProfile::Visit(ObjImpColl *obj)
{
    f_ris_fit = new TFile("../analisi_risoluzione_energia/risultati_fit_profile.root", "UPDATE");
    f_ris_fit->cd();

    f_ris_fit->Delete("fit_res_imp_coll;*");

    risultati_fit = obj->GetP()->Fit(obj->GetF(), "SR");
    risultati_fit->SetNameTitle("fit_res_imp_coll", "pol4");
    risultati_fit->Write();

    f_ris_fit->Close();

    std::cout << "fit ObjImpColl eseguito" << std::endl;
}

void ViFitProfile::Visit(ObjNonColl *obj)
{
    f_ris_fit = new TFile("../analisi_risoluzione_energia/risultati_fit_profile.root", "UPDATE");
    f_ris_fit->cd();

    f_ris_fit->Delete("fit_res_non_coll;*");

    risultati_fit = obj->GetP()->Fit(obj->GetF(), "SR");
    risultati_fit->SetNameTitle("fit_res_non_coll", "pol4");
    risultati_fit->Write();

    f_ris_fit->Close();

    std::cout << "fit ObjNonColl eseguito" << std::endl;
}

void ViFitProfile::Visit(ObjAn *obj)
{
    f_ris_fit = new TFile("../analisi_risoluzione_energia/risultati_fit_profile.root", "UPDATE");
    f_ris_fit->cd();

    f_ris_fit->Delete("fit_res_an_corr_1;*");
    f_ris_fit->Delete("fit_res_an_corr_2;*");
    f_ris_fit->Delete("fit_res_an_mean;*");
    f_ris_fit->Delete("fit_res_an_cos;*");

    risultati_fit = obj->GetPCorr()->Fit(obj->GetFCorr1(), "SR");
    risultati_fit->SetNameTitle("fit_res_an_corr_1", "pol1");
    risultati_fit->Write();
    risultati_fit = obj->GetPCorr()->Fit(obj->GetFCorr2(), "SR+");
    risultati_fit->SetNameTitle("fit_res_an_corr_2", "pol1");
    risultati_fit->Write();

    risultati_fit = obj->GetPMean()->Fit(obj->GetFMean(), "SR");
    risultati_fit->SetNameTitle("fit_res_an_mean", "pol4");
    risultati_fit->Write();

    risultati_fit = obj->GetPCos()->Fit(obj->GetFCos(), "SR");
    risultati_fit->SetNameTitle("fit_res_an_cos", "pol4");
    risultati_fit->Write();

    f_ris_fit->Close();

    std::cout << "fit ObjAn eseguito" << std::endl;
}

void ViFitProfile::Visit(ObjAnColl *obj) {} // TODO