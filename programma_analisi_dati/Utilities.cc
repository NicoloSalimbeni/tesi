
#include "TMacro.h"
#include "TF1.h"
#include "TLorentzVector.h"
#include "Utilities.h"
#include <iostream>

const Double_t Utilities::mass_B = 5.27915;

Double_t Utilities::SolveEq2_min(const Double_t &a, const Double_t &b, const Double_t &c)
{
    Double_t delta = b * b - 4 * a * c;
    Double_t sol_min = (-b - sqrt(delta)) / (2 * a);
    return sol_min;
}

Double_t Utilities::SolveEq2_mag(const Double_t &a, const Double_t &b, const Double_t &c)
{
    Double_t delta = b * b - 4 * a * c;
    Double_t sol_mag = (-b + sqrt(delta)) / (2 * a);
    return sol_mag;
}

Double_t Utilities::SolveEq2_cos(const Double_t &a, const Double_t &b, const Double_t &c, const TLorentzVector &tlv_v, const Double_t &pvz)
{
    Double_t delta = b * b - 4 * a * c;
    Double_t sol_mag = (-b + sqrt(delta)) / (2 * a);
    Double_t sol_min = (-b - sqrt(delta)) / (2 * a);
    Double_t pBp = sqrt(sol_mag * sol_mag - mass_B * mass_B);
    Double_t pBm = sqrt(sol_min * sol_min - mass_B * mass_B);
    Double_t cosp = (sol_mag * tlv_v.T() - (tlv_v.M2() + mass_B * mass_B) / 2) / (tlv_v.P() * pBp);
    Double_t cosm = (sol_min * tlv_v.T() - (tlv_v.M2() + mass_B * mass_B) / 2) / (tlv_v.P() * pBm);

    if (cosm < cosp)
    {
        return sol_mag;
    }
    else if (cosm > cosp)
    {
        return sol_min;
    }
    return -1;
}

Double_t Utilities::SolveEq2_post(const Double_t &a, const Double_t &b, const Double_t &c, const TLorentzVector &tlv_B)
{
    Double_t delta = b * b - 4 * a * c;
    Double_t sol_mag = (-b + sqrt(delta)) / (2 * a);
    Double_t sol_min = (-b - sqrt(delta)) / (2 * a);
    if (abs(sol_mag - tlv_B.T()) < abs(sol_min - tlv_B.T()))
    {
        return sol_mag;
    }
    else if (abs(sol_min - tlv_B.T()) < abs(sol_mag - tlv_B.T()))
    {
        return sol_min;
    }
    return -1;
}

Double_t Utilities::int_settore_circolare(Double_t a_min, Double_t a_max)
{
    return 2 * TMath::Pi() * (TMath::Cos(a_min) - TMath::Cos(a_max));
}
