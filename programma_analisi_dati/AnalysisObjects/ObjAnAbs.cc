#include "ObjAnAbs.h"
#include "TLorentzVector.h"
#include "TH2D.h"
#include "TProfile.h"
#include "../AnalysisFramework/Visitor.h"
#include "../AnalysisFramework/AnalysisSteering.h"
#include "../AnalysisFramework/AnalysisFactory.h"
#include "../AnalysisUtilities/Utilities.h"

ObjAnAbs::ObjAnAbs()
{
    n_tot = 0;
    n_tot_accettabili = 0;
    n_delta_negativo = 0;
    n_inconcludente_cos = 0;
}

ObjAnAbs::~ObjAnAbs()
{
    return;
}

void ObjAnAbs::LoadEnergyMag()
{
    ris = (en_B - sol_mag) / en_B;
    Resolution_an_mag->Fill(vis_mass, ris);
    h_residui_mag->Fill(ris);
}

void ObjAnAbs::LoadEnergyMin()
{
    ris = (en_B - sol_min) / en_B;
    Resolution_an_min->Fill(vis_mass, ris);
    h_residui_min->Fill(ris);
}

void ObjAnAbs::LoadEnergyMean()
{
    ris = (en_B - sol_mean) / en_B;
    Resolution_an_mean->Fill(vis_mass, ris);
    an_mean_profile->Fill(vis_mass, ris, 1);
    h_residui_mean->Fill(ris);
}

void ObjAnAbs::LoadEnergyCos()
{
    pBp = sqrt(sol_mag * sol_mag - tlv_Btag.M2());
    pBm = sqrt(sol_min * sol_min - tlv_Btag.M2());
    cosp = (sol_mag * en_vis - (vis_mass2 + tlv_Btag.M2()) / 2) / (p_vis * pBp);
    cosm = (sol_min * en_vis - (vis_mass2 + tlv_Btag.M2()) / 2) / (p_vis * pBm);

    if (cosm < cosp)
    {
        ris = (en_B - sol_mag) / en_B;
    }
    else if (cosm > cosp)
    {
        ris = (en_B - sol_min) / en_B;
    }
    else if (cosp == cosm)
    {
        n_inconcludente_cos++;
        return; // se l'analisi non è risolutiva si esce senza caricare il risultato
    }

    Resolution_an_cos->Fill(vis_mass, ris);
    an_cos_profile->Fill(vis_mass, ris, 1);
    h_residui_cos->Fill(ris);
}

void ObjAnAbs::LoadEnergyCorr()
{
    if (abs(sol_mag - en_B) < abs(sol_min - en_B))
    {
        ris = (en_B - sol_mag) / en_B;
    }
    else if (abs(sol_min - en_B) < abs(sol_mag - en_B))
    {
        ris = (en_B - sol_min) / en_B;
    }
    else
    {
        return; // se l'analisi non è risolutiva si esce senza caricare il risultato
    }

    Resolution_an_corr->Fill(vis_mass, ris);
    an_corr_profile->Fill(vis_mass, ris, 1);
    h_residui_corr->Fill(ris);
}

void ObjAnAbs::LoadEnergyCollComp()
{
    Double_t en_coll = en_vis * Utilities::mass_B / vis_mass;

    if (abs(sol_mag - en_coll) < abs(sol_min - en_coll))
    {
        ris = (en_B - sol_mag) / en_B;
    }
    else if (abs(sol_min - en_coll) < abs(sol_mag - en_coll))
    {
        ris = (en_B - sol_min) / en_B;
    }
    else
    {
        return; // se l'analisi non è risolutiva si esce senza caricare il risultato
    }

    Resolution_an_collcomp->Fill(vis_mass, ris);
    an_collcomp_profile->Fill(vis_mass, ris, 1);
    h_residui_collcomp->Fill(ris);
}

void ObjAnAbs::LoadEnergies()
{
    LoadEnergyMag();
    LoadEnergyMin();
    LoadEnergyMean();
    LoadEnergyCos();
    LoadEnergyCorr();
    LoadEnergyCollComp();
}

void ObjAnAbs::AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_v)
{
    n_tot++;

    tlv_Btag = tlv_B;
    tlv_visibile = tlv_v;

    en_vis = tlv_visibile.T();
    en_B = tlv_Btag.T();
    p_vis = tlv_visibile.P();
    vis_mass = tlv_visibile.M();
    vis_mass2 = tlv_visibile.M2();

    ComputeSolutions();
    if (sol_mag == TMath::Infinity() && sol_min == TMath::Infinity())
    {
        n_delta_negativo++;
        return; // controllo se il sistema è risolvibile altrimenti non caricare le energie;
    }
    n_tot_accettabili++;
    LoadEnergies();
}

TH2D *ObjAnAbs::GetHMin()
{
    return Resolution_an_min;
}

TH2D *ObjAnAbs::GetHMag()
{
    return Resolution_an_mag;
}

TH2D *ObjAnAbs::GetHMean()
{
    return Resolution_an_mean;
}

TH2D *ObjAnAbs::GetHCos()
{
    return Resolution_an_cos;
}

TH2D *ObjAnAbs::GetHCorr()
{
    return Resolution_an_corr;
}

TH2D *ObjAnAbs::GetHCollComp()
{
    return Resolution_an_collcomp;
}

TProfile *ObjAnAbs::GetPMean()
{
    return an_mean_profile;
}

TProfile *ObjAnAbs::GetPCos()
{
    return an_cos_profile;
}

TProfile *ObjAnAbs::GetPCorr()
{
    return an_corr_profile;
}

TProfile *ObjAnAbs::GetPCollComp()
{
    return an_collcomp_profile;
}

TF1 *ObjAnAbs::GetFCorr1()
{
    return f_fit_corr1;
}

TF1 *ObjAnAbs::GetFCorr2()
{
    return f_fit_corr2;
}

TF1 *ObjAnAbs::GetFCos()
{
    return f_fit_cos;
}

TF1 *ObjAnAbs::GetFMean()
{
    return f_fit_mean;
}

TF1 *ObjAnAbs::GetFCollComp()
{
    return f_fit_collcomp;
}

TFitResultPtr ObjAnAbs::GetFitProfileResultCos()
{
    return risultati_fit_cos;
}

TFitResultPtr ObjAnAbs::GetFitProfileResultCorr1()
{
    return risultati_fit_corr1;
}

TFitResultPtr ObjAnAbs::GetFitProfileResultCorr2()
{
    return risultati_fit_corr2;
}

TFitResultPtr ObjAnAbs::GetFitProfileResultMean()
{
    return risultati_fit_mean;
}

TFitResultPtr ObjAnAbs::GetFitProfileResultCollComp()
{
    return risultati_fit_collcomp;
}

TH1D *ObjAnAbs::GetHResiduiCorr()
{
    return h_residui_corr;
}

TH1D *ObjAnAbs::GetHResiduiCos()
{
    return h_residui_cos;
}

TH1D *ObjAnAbs::GetHResiduiMean()
{
    return h_residui_mean;
}

TH1D *ObjAnAbs::GetHResiduiMag()
{
    return h_residui_mag;
}

TH1D *ObjAnAbs::GetHResiduiMin()
{
    return h_residui_min;
}

TH1D *ObjAnAbs::GetHResiduiCollComp()
{
    return h_residui_collcomp;
}