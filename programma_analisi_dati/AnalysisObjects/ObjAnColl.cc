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

    Resolution_an_mag = new TH2D("Resolution_anColl_mag", "risoluzione vs massa visibile,  metodo analitico soluzione maggiore", 100, 1, 4.5, 300, -3.5, 1);
    Resolution_an_mag->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_mag->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_mag->GetZaxis()->SetTitle("Counts");
    Resolution_an_mag->SetStats(0);
    Resolution_an_mag->GetYaxis()->SetMaxDigits(1);
    Resolution_an_mag->GetZaxis()->SetMaxDigits(3);

    Resolution_an_min = new TH2D("Resolution_anColl_min", "risoluzione vs massa visibile,  metodo analitico soluzione minore", 100, 1, 4.5, 300, -0.5, 1);
    Resolution_an_min->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_min->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_min->GetZaxis()->SetTitle("Counts");
    Resolution_an_min->SetStats(0);
    Resolution_an_min->GetYaxis()->SetMaxDigits(1);
    Resolution_an_min->GetZaxis()->SetMaxDigits(3);

    Resolution_an_corr = new TH2D("Resolution_anColl_corr", "risoluzione vs massa visibile,  risultati esatti", 100, 1, 4.5, 300, -1, 1);
    Resolution_an_corr->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_corr->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_corr->GetZaxis()->SetTitle("Counts");
    Resolution_an_corr->SetStats(0);
    Resolution_an_corr->GetYaxis()->SetMaxDigits(1);
    Resolution_an_corr->GetZaxis()->SetMaxDigits(3);

    an_corr_profile = new TProfile("Profile_anColl_corr", "Profilo Massa vs risoluzione, risultati esatti", 25, 1, 4.5, -6, 6);
    an_corr_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_corr_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_corr_profile->SetStats(0);

    Resolution_an_mean = new TH2D("Resolution_anColl_mean", "risoluzione vs massa visibile,  media soluzioni analitiche", 100, 1, 4.5, 300, -3, 1);
    Resolution_an_mean->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_mean->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_mean->GetZaxis()->SetTitle("Counts");
    Resolution_an_mean->SetStats(0);
    Resolution_an_mean->GetYaxis()->SetMaxDigits(1);
    Resolution_an_mean->GetZaxis()->SetMaxDigits(3);

    an_mean_profile = new TProfile("Profile_anColl_mean", "Profilo Massa vs risoluzione, media soluzioni", 25, 1, 4.5, -6, 6);
    an_mean_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_mean_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_mean_profile->SetStats(0);

    Resolution_an_cos = new TH2D("Resolution_anColl_cos", "risoluzione vs massa visibile,  cos#theta maggiore", 100, 1, 4.5, 300, -3, 1.5);
    Resolution_an_cos->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_cos->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_cos->GetZaxis()->SetTitle("Counts");
    Resolution_an_cos->SetStats(0);
    Resolution_an_cos->GetYaxis()->SetMaxDigits(1);
    Resolution_an_cos->GetZaxis()->SetMaxDigits(3);

    an_cos_profile = new TProfile("Profile_anColl_cos", "Profilo Massa vs risoluzione,  cos#theta maggiore", 25, 1, 4.5, -6, 6);
    an_cos_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_cos_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_cos_profile->SetStats(0);

    // inizializzo le funzioni per eventuali fit
    f_fit_corr1 = new TF1("f_anColl_corr_1", "pol4", 1.5, 4);
    // f_fit_corr2 = new TF1("f_anColl_corr_2", "pol1", 3.2, 4);

    f_fit_mean = new TF1("f_anColl_mean", "pol4", 1, 4.2);

    f_fit_cos = new TF1("f_anColl_cos", "pol4", 1, 4);

    // inizializzo istogrammi
    Int_t nbin = 100;
    Float_t start = -3.5, stop = 1;
    Float_t binwidth = (stop - start) / nbin;
    std::string s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);

    h_residui_mag = new TH1D("Hist_residui_AnColl_mag", "residui percentuali analitica cos#theta=1 sol mag (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_mag->GetXaxis()->SetTitle("Residui");
    h_residui_mag->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -0.5, stop = 1;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);
    h_residui_min = new TH1D("Hist_residui_AnColl_min", "residui percentuali analitica cos#theta=1 sol min (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_min->GetXaxis()->SetTitle("Residui");
    h_residui_min->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -3, stop = 1;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);
    h_residui_mean = new TH1D("Hist_residui_AnColl_mean", "residui percentuali analitica cos#theta=1 media soluzioni (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_mean->GetXaxis()->SetTitle("Residui");
    h_residui_mean->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -3, stop = 2;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);
    h_residui_cos = new TH1D("Hist_residui_AnColl_cos", "residui percentuali analitica cos#theta=1 cos#theta > (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_cos->GetXaxis()->SetTitle("Residui");
    h_residui_cos->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -1, stop = 1;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);
    h_residui_corr = new TH1D("Hist_residui_AnColl_corr", "residui percentuali analitica cos#theta=1 posteriori (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_corr->GetXaxis()->SetTitle("Residui");
    h_residui_corr->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());
}

ObjAnColl::~ObjAnColl()
{
    return;
}

void ObjAnColl::AddPoint(const TLorentzVector &tlv_Btag, const TLorentzVector &tlv_visibile)
{
    Double_t sol_mag = util->GetSolMagColl();
    Double_t sol_min = util->GetSolMinColl();
    Double_t vis_mass = tlv_visibile.M();
    Double_t en_B = tlv_Btag.T();
    // soluzione analitica scelta con il coseno maggiore
    static Double_t en_cos;
    en_cos = util->GetSolCosColl();
    static Double_t res_an_cos;
    res_an_cos = (en_B - en_cos) / en_B;
    Resolution_an_cos->Fill(vis_mass, res_an_cos);
    an_cos_profile->Fill(vis_mass, res_an_cos, 1);
    h_residui_cos->Fill(res_an_cos);

    // entrambe le soluzioni con maggiore e minore
    Float_t ris_min = (en_B - sol_min) / en_B;
    Float_t ris_mag = (en_B - sol_mag) / en_B;

    Resolution_an_min->Fill(vis_mass, ris_min);
    Resolution_an_mag->Fill(vis_mass, ris_mag);
    h_residui_min->Fill(ris_min);
    h_residui_mag->Fill(ris_mag);

    // media delle soluzioni analitiche
    Double_t sol_mean = util->GetSolMeanColl();
    Double_t ris_an_mean;

    ris_an_mean = (en_B - sol_mean) / en_B;
    Resolution_an_mean->Fill(vis_mass, ris_an_mean);
    an_mean_profile->Fill(vis_mass, ris_an_mean, 1);
    h_residui_mean->Fill(ris_an_mean);

    // studio della soluzione scelta a posteriori
    static Double_t en_corr;
    en_corr = util->GetSolPostColl();
    static Double_t ris_an_corr;
    ris_an_corr = (en_B - en_corr) / en_B;
    Resolution_an_corr->Fill(vis_mass, ris_an_corr);
    an_corr_profile->Fill(vis_mass, ris_an_corr, 1);
    h_residui_corr->Fill(ris_an_corr);
}

void ObjAnColl::Accept(Visitor *v)
{
    v->Visit(this);
}