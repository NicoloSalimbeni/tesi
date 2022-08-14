#include "AnalysisObject.h"
#include "TH2D.h"
#include "TF1.h"
#include "TProfile.h"
#include "TLorentzVector.h"
#include "TFitResult.h"

AnalysisObject::AnalysisObject()
{
    return;
}

AnalysisObject::~AnalysisObject()
{
    delete hris;
    delete pris;
    delete f_fit;
}

TH2D *AnalysisObject::GetH() const
{
    return hris;
}

TProfile *AnalysisObject::GetP() const
{
    return pris;
}

TF1 *AnalysisObject::GetF() const
{
    return f_fit;
}

TFitResultPtr AnalysisObject::GetFitProfileResult() const
{
    return risultati_fit;
}

void AnalysisObject::Update(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis)
{
    AddPoint(tlv_B, tlv_vis);
}
