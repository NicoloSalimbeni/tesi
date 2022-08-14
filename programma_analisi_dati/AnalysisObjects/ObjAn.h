#ifndef ObjAn_h
#define ObjAn_h
#include "../AnalysisFramework/AnalysisObject.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TF1.h"
#include "TFitResult.h"

class TLorentVector;
class Visitor;

class ObjAn : public AnalysisObject
{
public:
    ObjAn();
    ~ObjAn();
    TH2D *GetHMin();
    TH2D *GetHMag();
    TH2D *GetHCos();
    TH2D *GetHMean();
    TH2D *GetHCorr();

    TProfile *GetPCos();
    TProfile *GetPMean();
    TProfile *GetPCorr();

    TF1 *GetFCos();
    TF1 *GetFCorr1();
    TF1 *GetFCorr2();
    TF1 *GetFMean();

    TFitResultPtr GetFitProfileResultCos();
    TFitResultPtr GetFitProfileResultCorr1();
    TFitResultPtr GetFitProfileResultCorr2();
    TFitResultPtr GetFitProfileResultMean();

    void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) override;
    void Accept(Visitor *) override;

private:
    // ignoro h2 in questo caso
    TH2D *Resolution_an_mag;  // sol maggiore
    TH2D *Resolution_an_min;  // sol minore
    TH2D *Resolution_an_cos;  // sol con coseno maggiore
    TH2D *Resolution_an_mean; // media delle soluzioni
    TH2D *Resolution_an_corr; // soluzione a posteriori

    TProfile *an_corr_profile;
    TProfile *an_cos_profile;
    TProfile *an_mean_profile;

    TF1 *f_fit_cos;
    TF1 *f_fit_corr1;
    TF1 *f_fit_corr2;
    TF1 *f_fit_mean;

    TFitResultPtr risultati_fit_cos;
    TFitResultPtr risultati_fit_corr1;
    TFitResultPtr risultati_fit_corr2;
    TFitResultPtr risultati_fit_mean;
};

#endif