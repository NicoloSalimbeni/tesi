#ifndef Utilities_h
#define Utilities_h

#include "TLorentzVector.h"
#include "Observer.h"

class Utilities : public Observer
{
public:
    Utilities();
    ~Utilities();
    static Double_t SolveEq2_mag(const Double_t &a, const Double_t &b, const Double_t &c);
    static Double_t SolveEq2_min(const Double_t &a, const Double_t &b, const Double_t &c);
    static Double_t SolveEq2_cos(const Double_t &a, const Double_t &b, const Double_t &c, const TLorentzVector &tlv_v, const Double_t &pvz);
    static Double_t SolveEq2_post(const Double_t &a, const Double_t &b, const Double_t &c, const TLorentzVector &tlv_B);
    static Double_t int_settore_circolare(Double_t a_min, Double_t a_max);
    static const Double_t mass_B; // in GeV

    void Update(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) override;

private:
    Double_t a;
    Double_t b;
    Double_t c;

    Double_t pvz;
    Double_t vis_mass;
    Double_t vis_mass2;

    Double_t delta;
    Double_t sol_mag;
    Double_t sol_min;
};

#endif
