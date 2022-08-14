
#include "TMacro.h"
#include "TF1.h"
#include "TLorentzVector.h"
#include "UtilitiesAnalytic.h"
#include <iostream>

UtilitiesAnalytic::UtilitiesAnalytic()
{
}

UtilitiesAnalytic::~UtilitiesAnalytic()
{
}

void UtilitiesAnalytic::SolveEq2_cos()
{
    Double_t pBp = sqrt(sol_mag * sol_mag - mass_B * mass_B);
    Double_t pBm = sqrt(sol_min * sol_min - mass_B * mass_B);
    Double_t cosp = (sol_mag * en_vis - (vis_mass2 + mass_B * mass_B) / 2) / (p_vis * pBp);
    Double_t cosm = (sol_min * en_vis - (vis_mass2 + mass_B * mass_B) / 2) / (p_vis * pBm);

    if (cosm < cosp)
    {
        sol_cos_coll = sol_mag_coll;
    }
    else if (cosm > cosp)
    {
        sol_cos_coll = sol_min_coll;
    }
    else
    {
        sol_cos_coll = -1;
    }

    Double_t pBp_coll = sqrt(sol_mag_coll * sol_mag_coll - mass_B * mass_B);
    Double_t pBm_coll = sqrt(sol_min_coll * sol_min_coll - mass_B * mass_B);
    Double_t cosp_coll = (sol_mag_coll * en_vis - (vis_mass2 + mass_B * mass_B) / 2) / (p_vis * pBp_coll);
    Double_t cosm_coll = (sol_min_coll * en_vis - (vis_mass2 + mass_B * mass_B) / 2) / (p_vis * pBm_coll);

    if (cosm_coll < cosp_coll)
    {
        sol_cos_coll = sol_mag_coll;
    }
    else if (cosm_coll > cosp_coll)
    {
        sol_cos_coll = sol_min_coll;
    }
    else
    {
        sol_cos_coll = -1;
    }
    return;
}

void UtilitiesAnalytic::SolveEq2_post()
{
    if (abs(sol_mag - en_B) < abs(sol_min - en_B))
    {
        sol_post_coll = sol_mag_coll;
    }
    else if (abs(sol_min - en_B) < abs(sol_mag - en_B))
    {
        sol_post_coll = sol_min_coll;
    }
    else
    {
        sol_post_coll = -1;
    }

    if (abs(sol_mag_coll - en_B) < abs(sol_min_coll - en_B))
    {
        sol_post_coll = sol_mag_coll;
    }
    else if (abs(sol_min - en_B) < abs(sol_mag - en_B))
    {
        sol_post_coll = sol_min_coll;
    }
    else
    {
        sol_post_coll = -1;
    }
    return;
}

void UtilitiesAnalytic::Update(const TLorentzVector &tlv_Btag, const TLorentzVector &tlv_visibile)
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

    // cout << "------Esatto" << endl;
    // cout << a << " " << b << " " << c << endl;
    // cout << a_coll << " " << b_coll << " " << c_coll << endl;
    // cout << mass_B << " " << tlv_Btag.M() << endl;
    sol_mag = SolveEq2(a, b, c, '+');
    sol_min = SolveEq2(a, b, c, '-');
    // cout << "------" << endl;

    a_coll = 4 * (pow(tlv_visibile.T(), 2) - tlv_visibile.P() * tlv_visibile.P());
    b_coll = -4 * tlv_visibile.T() * (vis_mass2 + tlv_Btag.M2());
    c_coll = 4 * pow(tlv_Btag.M() * tlv_visibile.P(), 2) + pow(tlv_Btag.M2() + vis_mass2, 2);

    // cout << "------Coll" << endl;
    // cout << a << " " << b << " " << c << endl;
    // cout << a_coll << " " << b_coll << " " << c_coll << endl;
    // cout << mass_B << " " << tlv_Btag.M() << endl;
    sol_mag_coll = SolveEq2(a_coll, b_coll, c_coll, '+');
    sol_min_coll = SolveEq2(a_coll, b_coll, c_coll, '-');
    // cout << "------" << endl;

    SolveEq2_cos();
    SolveEq2_post();

    return;
}

Double_t UtilitiesAnalytic::GetSolMag()
{
    return sol_mag;
}

Double_t UtilitiesAnalytic::GetSolMin()
{
    return sol_min;
}

Double_t UtilitiesAnalytic::GetSolMean()
{
    return (sol_mag + sol_min) / 2;
}

Double_t UtilitiesAnalytic::GetSolCos()
{
    return sol_cos;
}

Double_t UtilitiesAnalytic::GetSolPost()
{
    return sol_post;
}

Double_t UtilitiesAnalytic::GetSolMagColl()
{
    return sol_mag_coll;
}

Double_t UtilitiesAnalytic::GetSolMinColl()
{
    return sol_min_coll;
}

Double_t UtilitiesAnalytic::GetSolMeanColl()
{
    return (sol_mag_coll + sol_min_coll) / 2;
}

Double_t UtilitiesAnalytic::GetSolCosColl()
{
    return sol_cos_coll;
}

Double_t UtilitiesAnalytic::GetSolPostColl()
{
    return sol_post_coll;
}