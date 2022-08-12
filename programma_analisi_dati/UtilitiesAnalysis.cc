
#include "TMacro.h"
#include "TF1.h"
#include "TLorentzVector.h"
#include "UtilitiesAnalysis.h"
#include <iostream>

UtilitiesAnalysis::UtilitiesAnalysis()
{
}

UtilitiesAnalysis::~UtilitiesAnalysis()
{
}

void UtilitiesAnalysis::SolveEq2_cos()
{
    Double_t pBp = sqrt(sol_mag * sol_mag - mass_B * mass_B);
    Double_t pBm = sqrt(sol_min * sol_min - mass_B * mass_B);
    Double_t cosp = (sol_mag * en_vis - (vis_mass2 + mass_B * mass_B) / 2) / (p_vis * pBp);
    Double_t cosm = (sol_min * en_vis - (vis_mass2 + mass_B * mass_B) / 2) / (p_vis * pBm);

    if (cosm < cosp)
    {
        sol_cos = sol_mag;
    }
    else if (cosm > cosp)
    {
        sol_cos = sol_min;
    }
    else
    {
        sol_cos = -1;
    }
    return;
}

void UtilitiesAnalysis::SolveEq2_post()
{
    if (abs(sol_mag - en_B) < abs(sol_min - en_B))
    {
        sol_post = sol_mag;
    }
    else if (abs(sol_min - en_B) < abs(sol_mag - en_B))
    {
        sol_post = sol_min;
    }
    else
    {
        sol_post = -1;
    }
    return;
}

void UtilitiesAnalysis::Update(const TLorentzVector &tlv_Btag, const TLorentzVector &tlv_visibile)
{
    en_vis = tlv_visibile.T();
    en_B = tlv_Btag.T();
    p_vis = tlv_visibile.P();
    vis_mass = tlv_visibile.M();
    vis_mass2 = tlv_visibile.M2();

    pvz = (tlv_visibile.Vect().Dot(tlv_Btag.Vect())) / tlv_Btag.Vect().Mag();
    a = 4 * (pow(en_vis, 2) - pvz * pvz);
    b = -4 * en_vis * (vis_mass2 + tlv_Btag.M2());
    c = 4 * pow(tlv_Btag.M() * pvz, 2) + pow(tlv_Btag.M2() + vis_mass2, 2);

    sol_mag = SolveEq2(a, b, c, '+');
    sol_min = SolveEq2(a, b, c, '-');

    SolveEq2_cos();

    SolveEq2_post();

    return;
}

Double_t UtilitiesAnalysis::GetSolMag()
{
    return sol_mag;
}

Double_t UtilitiesAnalysis::GetSolMin()
{
    return sol_min;
}

Double_t UtilitiesAnalysis::GetSolMean()
{
    return (sol_mag + sol_min) / 2;
}

Double_t UtilitiesAnalysis::GetSolCos()
{
    return sol_cos;
}

Double_t UtilitiesAnalysis::GetSolPost()
{
    return sol_post;
}