#ifndef ObjAn_h
#define ObjAn_h
#include "../AnalysisFramework/AnalysisObject.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TF1.h"
#include "TFitResult.h"

class TLorentVector;
class Visitor;

class ObjAnAbs : public AnalysisObject
{
public:
    ObjAnAbs();
    virtual ~ObjAnAbs();
    virtual TH2D *GetHMin();
    virtual TH2D *GetHMag();
    virtual TH2D *GetHCos();
    virtual TH2D *GetHMean();
    virtual TH2D *GetHCorr();

    virtual TProfile *GetPCos();
    virtual TProfile *GetPMean();
    virtual TProfile *GetPCorr();

    virtual TF1 *GetFCos();
    virtual TF1 *GetFCorr1();
    virtual TF1 *GetFCorr2();
    virtual TF1 *GetFMean();

    virtual TFitResultPtr GetFitProfileResultCos();
    virtual TFitResultPtr GetFitProfileResultCorr1();
    virtual TFitResultPtr GetFitProfileResultCorr2();
    virtual TFitResultPtr GetFitProfileResultMean();

    virtual void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) = 0;
    virtual void Accept(Visitor *) = 0;

protected:
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