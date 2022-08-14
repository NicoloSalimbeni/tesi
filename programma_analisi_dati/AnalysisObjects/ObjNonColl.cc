#include "ObjNonColl.h"
#include "../AnalysisFramework/Visitor.h"
#include "../AnalysisFramework/AnalysisSteering.h"
#include "../AnalysisFramework/AnalysisFactory.h"

#include "TFitResult.h"

#include <string>

class ObjNonCollFactory : public AnalysisFactory::AbsFactory
{
public:
    ObjNonCollFactory() : AnalysisFactory::AbsFactory("ObjNonColl"){};
    AnalysisObject *create() override
    {
        return new ObjNonColl();
    }
};

static ObjNonCollFactory NonColl_static_factory;

ObjNonColl::ObjNonColl()
{
    AnalysisSteering::subscribe(this);

    hris = new TH2D("Resolution_non_coll", "risoluzione vs massa visibile non collinear", 100, 1, 4.5, 300, -3, 3);
    hris->GetXaxis()->SetTitle("massa visibile [GeV]");
    hris->GetYaxis()->SetTitle("risoluzione energia");
    hris->GetZaxis()->SetTitle("Counts");
    hris->SetStats(0);
    hris->GetZaxis()->SetMaxDigits(3);

    pris = new TProfile("Profile_non_coll", "Profilo Massa vs risoluzione non collinear", 25, 1, 4.5, -3, 3);
    pris->GetXaxis()->SetTitle("massa visibile [GeV]");
    pris->GetYaxis()->SetTitle("risoluzione energia");
    pris->SetStats(0);

    std::string grado_polinomio = "pol4";
    f_fit = new TF1("f_non_coll", grado_polinomio.c_str(), 1, 4.2);
    f_fit = new TF1("f_coll", grado_polinomio.c_str(), 1, 4.2);
}

ObjNonColl::~ObjNonColl()
{
}

void ObjNonColl::AddPoint(const TLorentzVector &tlv_Btag, const TLorentzVector &tlv_visibile)
{
    pvz = (tlv_visibile.Vect().Dot(tlv_Btag.Vect())) / tlv_Btag.Vect().Mag();
    en = (pow(tlv_Btag.M(), 2) + pow(tlv_visibile.M(), 2)) / (2 * tlv_visibile.T() - 2 * pvz);
    ris = (tlv_Btag.T() - en) / tlv_Btag.T();
    hris->Fill(tlv_visibile.M(), ris);
    pris->Fill(tlv_visibile.M(), ris, 1);
}

void ObjNonColl::Accept(Visitor *v)
{
    v->Visit(this);
}