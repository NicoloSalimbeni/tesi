#include "Utilities.h"
#include "TMath.h"
#include <iostream>

Utilities::Utilities()
{
}

Utilities::~Utilities()
{
}

const Double_t Utilities::mass_B = 5.27915;
const Double_t Utilities::mass_B2 = pow(5.27915, 2);

Double_t Utilities::SolveEq2(const Double_t &a, const Double_t &b, const Double_t &c, const char sol)
{
    double delta = b * b - 4 * a * c;
    if (delta < 0)
    {
        // std::cout << "Delta negativo: " << delta << std::endl;
        return TMath::Infinity();
    }
    switch (sol)
    {
    case '+':
        return (-b + sqrt(delta)) / (2 * a);
        break;
    case '-':
        return (-b - sqrt(delta)) / (2 * a);
        break;
    }
    return TMath::Infinity();
}

Double_t Utilities::int_settore_circolare(Double_t a_min, Double_t a_max)
{
    return 2 * TMath::Pi() * (TMath::Cos(a_min) - TMath::Cos(a_max));
}

void Utilities::ProgressBarr(float progress, int numero_progresso_corrente, int numero_progressi_totale)
{
    int barWidth = 70;
    std::cout << numero_progresso_corrente << "/" << numero_progressi_totale << " [";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}