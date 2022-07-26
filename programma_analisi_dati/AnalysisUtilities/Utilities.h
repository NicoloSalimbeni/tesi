// in questa classe ci saranno solamente funzioni static
// quando si va nel particolare per un'analisi specifica va creata una classe derivata

#ifndef Utilities_h
#define Utilities_h

#include "TH1D.h"

class Utilities
{
public:
    Utilities();
    ~Utilities();

    // funzioni static
    static Double_t SolveEq2(const Double_t &a, const Double_t &b, const Double_t &c, const char sol);
    static Double_t int_settore_circolare(Double_t a_min, Double_t a_max);
    static void ProgressBarr(float, int, int);
    // costanti utili
    static const Double_t mass_B;  // in GeV
    static const Double_t mass_B2; // in GeV

private:
};

#endif
