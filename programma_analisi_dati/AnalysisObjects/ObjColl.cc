#include "ObjColl.h"
#include "../AnalysisUtilities/Utilities.h"
#include "../AnalysisFramework/Visitor.h"
#include "../AnalysisFramework/AnalysisSteering.h"
#include "../AnalysisFramework/AnalysisFactory.h"

#include "TFitResult.h"

#include <string>

class ObjCollFactory : public AnalysisFactory::AbsFactory
{
public:
    ObjCollFactory() : AnalysisFactory::AbsFactory("ObjColl"){};
    AnalysisObject *create() override
    {
        return new ObjColl();
    }
};

static ObjCollFactory Coll_static_factory;

ObjColl::ObjColl()
{
    AnalysisSteering::subscribe(this);

    hris = new TH2D("Resolution_coll", "risoluzione vs massa Collinear", 100, 1, 4.5, 300, -3, 3);
    hris->GetXaxis()->SetTitle("massa visibile [GeV]");
    hris->GetYaxis()->SetTitle("risoluzione energia");
    hris->GetZaxis()->SetTitle("Counts");
    hris->SetStats(0);
    hris->GetZaxis()->SetMaxDigits(3);

    pris = new TProfile("Profile_coll", "Profilo Massa vs risoluzione collinear", 25, 1, 4.5, -3, 3);
    pris->GetXaxis()->SetTitle("massa visibile [GeV]");
    pris->GetYaxis()->SetTitle("risoluzione energia");
    pris->SetStats(0);

    std::string grado_polinomio = "pol4";
    f_fit = new TF1("f_coll", grado_polinomio.c_str(), 1, 4.2);

    Int_t nbin = 50;
    Float_t start = -3, stop = 1;
    Float_t binwidth = (stop - start) / nbin;
    std::string s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);
    h_residui = new TH1D("Hist_residui_Coll", "residui percentuali Collinear (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui->GetXaxis()->SetTitle("Residui");
    h_residui->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());
}

ObjColl::~ObjColl()
{
}

void ObjColl::AddPoint(const TLorentzVector &tlv_Btag, const TLorentzVector &tlv_visibile, const TLorentzVector &tlv_vertex)
{
    Double_t visible_energy = tlv_visibile.T();
    Double_t visible_mass = tlv_visibile.M();
    Double_t B_energy = tlv_Btag.T();

    Double_t en = visible_energy * Utilities::mass_B / visible_mass;
    ris = (B_energy - en) / B_energy;
    hris->Fill(visible_mass, ris);
    pris->Fill(visible_mass, ris, 1);
    h_residui->Fill(ris);
}

void ObjColl::Accept(Visitor *v)
{
    v->Visit(this);
}