#ifndef Utilities_h
#define Utilities_h

#include "TLorentzVector.h"

class Utilities
{
public:
    static Double_t SolveEq2_mag(const Double_t &a, const Double_t &b, const Double_t &c);
    static Double_t SolveEq2_min(const Double_t &a, const Double_t &b, const Double_t &c);
    static Double_t SolveEq2_cos(const Double_t &a, const Double_t &b, const Double_t &c, const TLorentzVector &tlv_v, const Double_t &pvz);
    static Double_t SolveEq2_post(const Double_t &a, const Double_t &b, const Double_t &c, const TLorentzVector &tlv_B);

    static Double_t int_settore_circolare(Double_t a_min, Double_t a_max);

    static const Double_t mass_B; // in GeV

private:
    Utilities();
    ~Utilities();
};

#endif
