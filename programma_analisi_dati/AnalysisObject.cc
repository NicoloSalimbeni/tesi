#include "AnalysisObject.h"
#include "TH2D.h"
#include "TF1.h"
#include "TProfile.h"
#include "TLorentzVector.h"

AnalysisObject::AnalysisObject()
{
    return;
}

AnalysisObject::~AnalysisObject()
{
    delete h2;
    delete p;
    delete f_fit;
}

TH2D *AnalysisObject::GetH() const
{
    return h2;
}

TProfile *AnalysisObject::GetP() const
{
    return p;
}

TF1 *AnalysisObject::GetF() const
{
    return f_fit;
}

void AnalysisObject::Update(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis)
{
    AddPoint(tlv_B, tlv_vis);
}
