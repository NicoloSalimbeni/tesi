#include "ObjAnColl.h"
#include "TLorentzVector.h"
#include "TH2D.h"
#include "TProfile.h"
#include "../AnalysisPlugins/UtilitiesAnalytic.h"
#include "../AnalysisFramework/Visitor.h"
#include "../AnalysisFramework/AnalysisSteering.h"
#include "../AnalysisFramework/AnalysisFactory.h"

extern UtilitiesAnalytic *util;

class ObjAnCollFactory : public AnalysisFactory::AbsFactory
{
public:
    ObjAnCollFactory() : AnalysisFactory::AbsFactory("ObjAnColl"){};
    AnalysisObject *create() override
    {

        return new ObjAnColl();
    }
};

static ObjAnCollFactory AnColl_static_factory;

ObjAnColl::ObjAnColl()
{

    AnalysisSteering::subscribe(this);

    Resolution_an_mag = new TH2D("Resolution_anColl_mag", "risoluzione vs massa visibile,  metodo analitico soluzione maggiore", 100, 1, 4.5, 300, -0.004, 0);
    Resolution_an_mag->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_mag->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_mag->GetZaxis()->SetTitle("Counts");
    Resolution_an_mag->SetStats(0);
    Resolution_an_mag->GetYaxis()->SetMaxDigits(1);
    Resolution_an_mag->GetZaxis()->SetMaxDigits(3);

    Resolution_an_min = new TH2D("Resolution_anColl_min", "risoluzione vs massa visibile,  metodo analitico soluzione minore", 100, 1, 4.5, 300, 0, 0.01);
    Resolution_an_min->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_min->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_min->GetZaxis()->SetTitle("Counts");
    Resolution_an_min->SetStats(0);
    Resolution_an_min->GetYaxis()->SetMaxDigits(1);
    Resolution_an_min->GetZaxis()->SetMaxDigits(3);

    Resolution_an_corr = new TH2D("Resolution_anColl_corr", "risoluzione vs massa visibile,  risultati esatti", 100, 1, 4.5, 300, -0.004, 0.004);
    Resolution_an_corr->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_corr->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_corr->GetZaxis()->SetTitle("Counts");
    Resolution_an_corr->SetStats(0);
    Resolution_an_corr->GetYaxis()->SetMaxDigits(1);
    Resolution_an_corr->GetZaxis()->SetMaxDigits(3);

    an_corr_profile = new TProfile("Profile_anColl_corr", "Profilo Massa vs risoluzione, risultati esatti", 25, 1, 4.5, -3, 3);
    an_corr_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_corr_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_corr_profile->SetStats(0);

    Resolution_an_mean = new TH2D("Resolution_anColl_mean", "risoluzione vs massa visibile,  media soluzioni analitiche", 100, 1, 4.5, 300, -1, 1);
    Resolution_an_mean->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_mean->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_mean->GetZaxis()->SetTitle("Counts");
    Resolution_an_mean->SetStats(0);
    Resolution_an_mean->GetYaxis()->SetMaxDigits(1);
    Resolution_an_mean->GetZaxis()->SetMaxDigits(3);

    an_mean_profile = new TProfile("Profile_anColl_mean", "Profilo Massa vs risoluzione, media soluzioni", 25, 1, 4.5, -3, 3);
    an_mean_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_mean_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_mean_profile->SetStats(0);

    Resolution_an_cos = new TH2D("Resolution_anColl_cos", "risoluzione vs massa visibile,  cos#theta maggiore", 100, 1, 4.5, 300, -0.004, 0.004);
    Resolution_an_cos->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_cos->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_cos->GetZaxis()->SetTitle("Counts");
    Resolution_an_cos->SetStats(0);
    Resolution_an_cos->GetYaxis()->SetMaxDigits(1);
    Resolution_an_cos->GetZaxis()->SetMaxDigits(3);

    an_cos_profile = new TProfile("Profile_anColl_cos", "Profilo Massa vs risoluzione,  cos#theta maggiore", 25, 1, 4.5, -3, 3);
    an_cos_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_cos_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_cos_profile->SetStats(0);

    // inizializzo le funzioni per eventuali fit
    f_fit_corr1 = new TF1("f_anColl_corr_1", "pol1", 1.5, 3.2);
    f_fit_corr2 = new TF1("f_anColl_corr_2", "pol1", 3.2, 4);

    f_fit_mean = new TF1("f_anColl_mean", "pol4", 1, 4.2);

    f_fit_cos = new TF1("f_anColl_cos", "pol4", 1, 4);
}

ObjAnColl::~ObjAnColl()
{
    return;
}

void ObjAnColl::AddPoint(const TLorentzVector &tlv_Btag, const TLorentzVector &tlv_visibile)
{
    Double_t sol_mag = util->GetSolMag();
    Double_t sol_min = util->GetSolMin();
    Double_t vis_mass = tlv_visibile.M();
    Double_t en_B = tlv_Btag.T();
    // soluzione analitica scelta con il coseno maggiore
    static Double_t en_cos;
    en_cos = util->GetSolCos();
    static Double_t res_an_cos;
    res_an_cos = (en_B - en_cos) / en_B;
    Resolution_an_cos->Fill(vis_mass, res_an_cos);
    an_cos_profile->Fill(vis_mass, res_an_cos, 1);

    // entrambe le soluzioni con maggiore e minore
    Resolution_an_min->Fill(vis_mass, (en_B - sol_min) / en_B);
    Resolution_an_mag->Fill(vis_mass, (en_B - sol_mag) / en_B);

    // media delle soluzioni analitiche
    Double_t sol_mean = util->GetSolMean();
    Double_t ris_an_mean;

    ris_an_mean = (en_B - sol_mean) / en_B;
    Resolution_an_mean->Fill(vis_mass, ris_an_mean);
    an_mean_profile->Fill(vis_mass, ris_an_mean, 1);

    // studio della soluzione scelta a posteriori
    static Double_t en_corr;
    en_corr = util->GetSolPost();
    static Double_t ris_an_corr;
    ris_an_corr = (en_B - en_corr) / en_B;
    Resolution_an_corr->Fill(vis_mass, ris_an_corr);
    an_corr_profile->Fill(vis_mass, ris_an_corr, 1);
}

void ObjAnColl::Accept(Visitor *v)
{
    v->Visit(this);
}