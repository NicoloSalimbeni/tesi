#include "ObjAnAbs.h"
#include "TLorentzVector.h"
#include "TH2D.h"
#include "TProfile.h"
#include "../AnalysisPlugins/UtilitiesAnalytic.h"
#include "../AnalysisFramework/Visitor.h"
#include "../AnalysisFramework/AnalysisSteering.h"
#include "../AnalysisFramework/AnalysisFactory.h"

UtilitiesAnalytic *util = new UtilitiesAnalytic();

ObjAnAbs::ObjAnAbs()
{
}

ObjAnAbs::~ObjAnAbs()
{
    return;
}

TH2D *ObjAnAbs::GetHMin()
{
    return Resolution_an_min;
}

TH2D *ObjAnAbs::GetHMag()
{
    return Resolution_an_mag;
}

TH2D *ObjAnAbs::GetHMean()
{
    return Resolution_an_mean;
}

TH2D *ObjAnAbs::GetHCos()
{
    return Resolution_an_cos;
}

TH2D *ObjAnAbs::GetHCorr()
{
    return Resolution_an_corr;
}

TProfile *ObjAnAbs::GetPMean()
{
    return an_mean_profile;
}

TProfile *ObjAnAbs::GetPCos()
{
    return an_cos_profile;
}

TProfile *ObjAnAbs::GetPCorr()
{
    return an_corr_profile;
}

TF1 *ObjAnAbs::GetFCorr1()
{
    return f_fit_corr1;
}

TF1 *ObjAnAbs::GetFCorr2()
{
    return f_fit_corr2;
}

TF1 *ObjAnAbs::GetFCos()
{
    return f_fit_cos;
}

TF1 *ObjAnAbs::GetFMean()
{
    return f_fit_mean;
}

TFitResultPtr ObjAnAbs::GetFitProfileResultCos()
{
    return risultati_fit_cos;
}

TFitResultPtr ObjAnAbs::GetFitProfileResultCorr1()
{
    return risultati_fit_corr1;
}

TFitResultPtr ObjAnAbs::GetFitProfileResultCorr2()
{
    return risultati_fit_corr2;
}

TFitResultPtr ObjAnAbs::GetFitProfileResultMean()
{
    return risultati_fit_mean;
}

TH1D *ObjAnAbs::GetHResiduiCorr()
{
    return h_residui_corr;
}

TH1D *ObjAnAbs::GetHResiduiCos()
{
    return h_residui_cos;
}

TH1D *ObjAnAbs::GetHResiduiMean()
{
    return h_residui_mean;
}

TH1D *ObjAnAbs::GetHResiduiMag()
{
    return h_residui_mag;
}

TH1D *ObjAnAbs::GetHResiduiMin()
{
    return h_residui_min;
}
