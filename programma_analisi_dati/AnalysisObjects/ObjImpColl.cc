#include "ObjImpColl.h"
#include "../AnalysisFramework/Visitor.h"
#include "../AnalysisFramework/AnalysisSteering.h"
#include "../AnalysisFramework/AnalysisSteering.h"
#include "../AnalysisFramework/AnalysisFactory.h"

#include "TFitResult.h"

#include <string>

class ObjImpCollFactory : public AnalysisFactory::AbsFactory
{
public:
    ObjImpCollFactory() : AnalysisFactory::AbsFactory("ObjImpColl"){};
    AnalysisObject *create() override
    {
        return new ObjImpColl();
    }
};

static ObjImpCollFactory ImpColl_static_factory;

ObjImpColl::ObjImpColl()
{
    AnalysisSteering::subscribe(this);

    hris = new TH2D("Resolution_imp_coll", "risoluzione vs massa visibile improved collinear", 100, 1, 4.5, 300, -3, 1);
    hris->GetXaxis()->SetTitle("massa visibile [GeV]");
    hris->GetYaxis()->SetTitle("risoluzione energia");
    hris->GetZaxis()->SetTitle("Counts");
    hris->SetStats(0);
    hris->GetZaxis()->SetMaxDigits(3);

    pris = new TProfile("Profile_imp_coll", "Profilo Massa vs risoluzione improved collinear", 25, 1, 4.5, -3, 3);
    pris->GetXaxis()->SetTitle("massa visibile [GeV]");
    pris->GetYaxis()->SetTitle("risoluzione energia");
    pris->SetStats(0);

    std::string grado_polinomio = "pol4";
    f_fit = new TF1("f_imp_coll", grado_polinomio.c_str(), 1, 4.2);
    f_fit = new TF1("f_coll", grado_polinomio.c_str(), 1, 4.2);
}

ObjImpColl::~ObjImpColl()
{
}

void ObjImpColl::AddPoint(const TLorentzVector &tlv_Btag, const TLorentzVector &tlv_visibile)
{
    en = (tlv_Btag.M2() + tlv_visibile.M2()) * (tlv_visibile.T() + tlv_visibile.P()) / (2 * tlv_visibile.M2());
    ris = (tlv_Btag.T() - en) / tlv_Btag.T();
    hris->Fill(tlv_visibile.M(), ris);
    pris->Fill(tlv_visibile.M(), ris, 1);
}

void ObjImpColl::Accept(Visitor *v)
{
    v->Visit(this);
}