#include "ObjColl.h"
#include "../AnalysisUtilities/Utilities.h"

ObjColl::ObjColl()
{
    hris = new TH2D("Resolution_coll", "risoluzione vs massa hrisear", 100, 1, 4.5, 300, -3, 1);
    hris->GetXaxis()->SetTitle("massa visibile [GeV]");
    hris->GetYaxis()->SetTitle("risoluzione energia");
    hris->GetZaxis()->SetTitle("Counts");
    hris->SetStats(0);
    hris->GetZaxis()->SetMaxDigits(3);

    pris = new TProfile("Profile_coll", "Profilo Massa vs risoluzione collinear", 25, 1, 4.5, -3, 1);
    pris->GetXaxis()->SetTitle("massa visibile [GeV]");
    pris->GetYaxis()->SetTitle("risoluzione energia");
    pris->SetStats(0);

    f_fit = new TF1("f_coll", "pol4", 1, 4.2);
}

ObjColl::~ObjColl()
{
}

void ObjColl::AddPoint(const TLorentzVector &tlv_Btag, const TLorentzVector &tlv_visibile)
{
    en = tlv_visibile.T() * Utilities::mass_B / tlv_visibile.M();
    ris = (tlv_Btag.T() - en) / tlv_Btag.T();
    hris->Fill(tlv_visibile.M(), ris);
    pris->Fill(tlv_visibile.M(), ris, 1);
}