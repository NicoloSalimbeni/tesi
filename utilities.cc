#ifndef utilities_h
#define utilities_h

#include "TMacro.h"
#include "TF1.h"
#include "TLorentzVector.h"

#include <iostream>

Double_t mass_B = 5.27915; // in Gev
Double_t sol_mag;
Double_t sol_min;
Double_t solve_eq2(Double_t a, Double_t b, Double_t c, TLorentzVector tlv_v, Double_t pvz, TLorentzVector tlv_B, char op)
{
    Double_t delta = b * b - 4 * a * c;
    sol_mag = (-b + sqrt(delta)) / (2 * a);
    sol_min = (-b - sqrt(delta)) / (2 * a);
    if (delta < 0)
    {
        std::cout << "delta negativo" << std::endl;
        return -1;
    }
    if (op == '+')
    {
        return sol_mag;
    }
    else if (op == '-')
    {
        return sol_min;
    }
    if (op == 'c')
    {
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
    }

    // Double_t mag = abs(2 * sol_mag * tlv_v.T() - 2 * sqrt(sol_mag * sol_mag - 5.27915 * 5.27915) * pvz - 5.27915 * 5.27915 - tlv_v.M2());
    // Double_t min = abs(2 * sol_min * tlv_v.T() - 2 * sqrt(sol_min * sol_min - 5.27915 * 5.27915) * pvz - 5.27915 * 5.27915 - tlv_v.M2());

    // if (mag < min)
    // {
    //     return sol_mag;
    // }
    // else if (min < mag)
    // {
    //     return sol_min;
    // }

    // verifica informatica, in questo modo ho controllato che effettivamente c'è una soluzione esatta
    if (op == 'i' && abs(sol_mag - tlv_B.T()) < abs(sol_min - tlv_B.T()))
    {
        return sol_mag;
    }
    else if (op == 'i' && abs(sol_min - tlv_B.T()) < abs(sol_mag - tlv_B.T()))
    {
        return sol_min;
    }

    // Double_t mag = (2 * sol_mag * tlv_v.T() - 5.27915 * 5.27915 - tlv_v.M2()) / (2 * pvz);
    // Double_t min = (2 * sol_min * tlv_v.T() - 5.27915 * 5.27915 - tlv_v.M2()) / (2 * pvz);

    // if (mag > 0 && min < 0)
    // {
    //     return sol_mag;
    // }
    // else if (mag < 0 && min > 0)
    // {
    //     return sol_min;
    // }
    // else if (mag > 0 && min > 0)
    // {
    //     cout << "entrambi positivi" << endl;
    // }
    // else if (mag < 0 && min < 0)
    // {
    //     cout << "entrambi negativi" << endl;
    // }

    return -1;
}

Double_t int_settore_circolare(Double_t a_min, Double_t a_max)
{
    return 2 * TMath::Pi() * (TMath::Cos(a_min) - TMath::Cos(a_max));
}

#endif