#ifndef AnalysisObject_h
#define AnalysisObject_h
#include "Observer.h"

#include "TH2D.h"
#include "TH1D.h"
#include "TF1.h"
#include "TProfile.h"
#include "TFitResultPtr.h"
#include "Visitor.h"

class AnalysisObject : public Observer
{
public:
    AnalysisObject();
    virtual ~AnalysisObject();

    virtual void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis, const TLorentzVector &tlv_vertex) = 0;
    void Update(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis, const TLorentzVector &tlv_vertex) override;

    TH2D *GetH() const;
    TProfile *GetP() const;
    TF1 *GetF() const;
    TH1D *GetHResidui() const;

    TFitResultPtr GetFitProfileResult() const;
    virtual void Accept(Visitor *) = 0;

protected:
    TH2D *hris;
    TProfile *pris;
    TF1 *f_fit;
    TH1D *h_residui;
    TFitResultPtr risultati_fit;

    Double_t ris;
    Double_t en;
};

#endif