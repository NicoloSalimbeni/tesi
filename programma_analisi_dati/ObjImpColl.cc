#include "ObjImpColl.h"
#include "Utilities.h"

ObjImpColl::ObjImpColl()
{
    hris = new TH2D("Resolution_imp_coll", "risoluzione vs massa visibile improved collinear", 100, 1, 4.5, 300, -3, 1);
    hris->GetXaxis()->SetTitle("massa visibile [GeV]");
    hris->GetYaxis()->SetTitle("risoluzione energia");
    hris->GetZaxis()->SetTitle("Counts");
    hris->SetStats(0);
    hris->GetZaxis()->SetMaxDigits(3);

    pris = new TProfile("Profile_imp_coll", "Profilo Massa vs risoluzione improved collinear", 25, 1, 4.5, -3, 1);
    pris->GetXaxis()->SetTitle("massa visibile [GeV]");
    pris->GetYaxis()->SetTitle("risoluzione energia");
    pris->SetStats(0);

    f_fit = new TF1("f_imp_coll", "pol4", 1, 4.2);
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