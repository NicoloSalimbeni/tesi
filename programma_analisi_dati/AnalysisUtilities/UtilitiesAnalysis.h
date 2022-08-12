// questa classe gestisce l'analisi della soluzione analitica
#ifndef UtilitiesAnalysis_h
#define UtilitiesAnalysis_h

#include "TLorentzVector.h"
#include "Utilities.h"

class UtilitiesAnalysis : public Utilities
{
public:
    UtilitiesAnalysis();
    ~UtilitiesAnalysis();

    Double_t GetSolMag();
    Double_t GetSolMin();
    Double_t GetSolMean();
    Double_t GetSolCos();
    Double_t GetSolPost();

    void Update(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis);

private:
    void SolveEq2_cos();
    void SolveEq2_post();

    Double_t en_vis;
    Double_t en_B;
    Double_t p_vis;
    Double_t pvz;
    Double_t vis_mass;
    Double_t vis_mass2;

    Double_t a;
    Double_t b;
    Double_t c;

    Double_t delta;
    Double_t sol_mag;
    Double_t sol_min;
    Double_t sol_cos;
    Double_t sol_post;
};

#endif
