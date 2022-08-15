#include "../AnalysisObjects/ObjColl.h"
#include "../AnalysisObjects/ObjImpColl.h"
#include "../AnalysisObjects/ObjNonColl.h"
#include "../AnalysisObjects/ObjAnEs.h"
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

    std::cout << "fit ObjColl executed" << std::endl;
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

    std::cout << "fit ObjImpColl executed" << std::endl;
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

    std::cout << "fit ObjNonColl executed" << std::endl;
}

void ViFitProfile::Visit(ObjAnEs *obj)
{
    f_ris_fit = new TFile("../analisi_risoluzione_energia/risultati_fit_profile.root", "UPDATE");
    f_ris_fit->cd();

    f_ris_fit->Delete("fit_res_anEs_corr_1;*");
    f_ris_fit->Delete("fit_res_anEs_corr_2;*");
    f_ris_fit->Delete("fit_res_anEs_mean;*");
    f_ris_fit->Delete("fit_res_anEs_cos;*");

    risultati_fit = obj->GetPCorr()->Fit(obj->GetFCorr1(), "SR");
    risultati_fit->SetNameTitle("fit_res_anEs_corr_1", "pol1");
    risultati_fit->Write();
    risultati_fit = obj->GetPCorr()->Fit(obj->GetFCorr2(), "SR+");
    risultati_fit->SetNameTitle("fit_res_anEs_corr_2", "pol1");
    risultati_fit->Write();

    risultati_fit = obj->GetPMean()->Fit(obj->GetFMean(), "SR");
    risultati_fit->SetNameTitle("fit_res_anEs_mean", "pol4");
    risultati_fit->Write();

    risultati_fit = obj->GetPCos()->Fit(obj->GetFCos(), "SR");
    risultati_fit->SetNameTitle("fit_res_anEs_cos", "pol4");
    risultati_fit->Write();

    f_ris_fit->Close();

    std::cout << "fit ObjAnEs executed" << std::endl;
}

void ViFitProfile::Visit(ObjAnColl *obj)
{
    f_ris_fit = new TFile("../analisi_risoluzione_energia/risultati_fit_profile.root", "UPDATE");
    f_ris_fit->cd();

    f_ris_fit->Delete("fit_res_anColl_corr_1;*");
    // f_ris_fit->Delete("fit_res_anColl_corr_2;*");
    f_ris_fit->Delete("fit_res_anColl_mean;*");
    f_ris_fit->Delete("fit_res_anColl_cos;*");

    risultati_fit = obj->GetPCorr()->Fit(obj->GetFCorr1(), "SR");
    risultati_fit->SetNameTitle("fit_res_anColl_corr_1", "pol4");
    risultati_fit->Write();
    // risultati_fit = obj->GetPCorr()->Fit(obj->GetFCorr2(), "SR+");
    // risultati_fit->SetNameTitle("fit_res_anColl_corr_2", "pol1");
    // risultati_fit->Write();

    risultati_fit = obj->GetPMean()->Fit(obj->GetFMean(), "SR");
    risultati_fit->SetNameTitle("fit_res_anColl_mean", "pol4");
    risultati_fit->Write();

    risultati_fit = obj->GetPCos()->Fit(obj->GetFCos(), "SR");
    risultati_fit->SetNameTitle("fit_res_anColl_cos", "pol4");
    risultati_fit->Write();

    f_ris_fit->Close();

    std::cout << "fit ObjAnColl executed" << std::endl;
} // TODO