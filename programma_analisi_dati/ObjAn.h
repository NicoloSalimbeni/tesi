#ifndef ObjAn_h
#define ObjAn_h
#include "AnalysisObject.h"
#include "TH2D.h"
#include "TProfile.h"

class TLorentVector;

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

    void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) override;

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
};

#endif