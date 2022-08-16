#ifndef ObjAn_h
#define ObjAn_h
#include "../AnalysisFramework/AnalysisObject.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TH1D.h"
#include "TLorentzVector.h"

class Visitor;

class ObjAnAbs : public AnalysisObject
{
public:
    ObjAnAbs();
    virtual ~ObjAnAbs();

    virtual void LoadEnergyMag();
    virtual void LoadEnergyMin();
    virtual void LoadEnergyMean();
    virtual void LoadEnergyCos();
    virtual void LoadEnergyCorr();
    virtual void LoadEnergyCollComp();

    virtual void LoadEnergies();
    virtual void ComputeSolutions() = 0;
    virtual void PrintFinalStats() = 0;

    virtual TH2D *GetHMin();
    virtual TH2D *GetHMag();
    virtual TH2D *GetHCos();
    virtual TH2D *GetHMean();
    virtual TH2D *GetHCorr();
    virtual TH2D *GetHCollComp();

    virtual TProfile *GetPCos();
    virtual TProfile *GetPMean();
    virtual TProfile *GetPCorr();
    virtual TProfile *GetPCollComp();

    virtual TF1 *GetFCos();
    virtual TF1 *GetFCorr1();
    virtual TF1 *GetFCorr2();
    virtual TF1 *GetFMean();
    virtual TF1 *GetFCollComp();

    virtual TFitResultPtr GetFitProfileResultCos();
    virtual TFitResultPtr GetFitProfileResultCorr1();
    virtual TFitResultPtr GetFitProfileResultCorr2();
    virtual TFitResultPtr GetFitProfileResultMean();
    virtual TFitResultPtr GetFitProfileResultCollComp();

    virtual TH1D *GetHResiduiMag();
    virtual TH1D *GetHResiduiMin();
    virtual TH1D *GetHResiduiCos();
    virtual TH1D *GetHResiduiMean();
    virtual TH1D *GetHResiduiCorr();
    virtual TH1D *GetHResiduiCollComp();

    virtual void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) override;
    virtual void Accept(Visitor *) override = 0;

protected:
    // ignoro h2 in questo caso
    TH2D *Resolution_an_mag;      // sol maggiore
    TH2D *Resolution_an_min;      // sol minore
    TH2D *Resolution_an_cos;      // sol con coseno maggiore
    TH2D *Resolution_an_mean;     // media delle soluzioni
    TH2D *Resolution_an_corr;     // soluzione a posteriori
    TH2D *Resolution_an_collcomp; //

    TProfile *an_corr_profile;
    TProfile *an_cos_profile;
    TProfile *an_mean_profile;
    TProfile *an_collcomp_profile;

    TF1 *f_fit_cos;
    TF1 *f_fit_corr1;
    TF1 *f_fit_corr2;
    TF1 *f_fit_mean;
    TF1 *f_fit_collcomp;

    TH1D *h_residui_mag;
    TH1D *h_residui_min;
    TH1D *h_residui_cos;
    TH1D *h_residui_mean;
    TH1D *h_residui_corr;
    TH1D *h_residui_collcomp;

    TFitResultPtr risultati_fit_cos;
    TFitResultPtr risultati_fit_corr1;
    TFitResultPtr risultati_fit_corr2;
    TFitResultPtr risultati_fit_mean;
    TFitResultPtr risultati_fit_collcomp;

    TLorentzVector tlv_Btag;
    TLorentzVector tlv_visibile;

    Double_t sol_min;
    Double_t sol_mag;
    Double_t sol_mean;
    Double_t ris;

    Double_t n_tot;
    Double_t n_tot_accettabili;
    Double_t n_delta_negativo;
    Double_t n_inconcludente_cos;

    Double_t vis_mass;
    Double_t vis_mass2;
    Double_t en_vis;
    Double_t p_vis;
    Double_t en_B;
    Double_t pBp;
    Double_t pBm;
    Double_t cosp;
    Double_t cosm;
};

#endif