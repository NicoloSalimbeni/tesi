#include "ObjAnColl.h"
#include "TLorentzVector.h"
#include "TH2D.h"
#include "TProfile.h"
#include "../AnalysisUtilities/Utilities.h"
#include "../AnalysisFramework/Visitor.h"
#include "../AnalysisFramework/AnalysisSteering.h"
#include "../AnalysisFramework/AnalysisFactory.h"

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

    Resolution_an_mag = new TH2D("Resolution_anColl_mag", "risoluzione vs massa visibile cos#theta=1,  metodo analitico soluzione maggiore", 100, 1, 4.5, 300, -3.5, 1);
    Resolution_an_mag->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_mag->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_mag->GetZaxis()->SetTitle("Counts");
    Resolution_an_mag->SetStats(0);
    Resolution_an_mag->GetYaxis()->SetMaxDigits(1);
    Resolution_an_mag->GetZaxis()->SetMaxDigits(3);

    Resolution_an_min = new TH2D("Resolution_anColl_min", "risoluzione vs massa visibile cos#theta=1,  metodo analitico soluzione minore", 100, 1, 4.5, 300, -0.5, 1);
    Resolution_an_min->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_min->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_min->GetZaxis()->SetTitle("Counts");
    Resolution_an_min->SetStats(0);
    Resolution_an_min->GetYaxis()->SetMaxDigits(1);
    Resolution_an_min->GetZaxis()->SetMaxDigits(3);

    Resolution_an_corr = new TH2D("Resolution_anColl_corr", "risoluzione vs massa visibile cos#theta=1,  risultati esatti", 100, 1, 4.5, 300, -1, 1);
    Resolution_an_corr->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_corr->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_corr->GetZaxis()->SetTitle("Counts");
    Resolution_an_corr->SetStats(0);
    Resolution_an_corr->GetYaxis()->SetMaxDigits(1);
    Resolution_an_corr->GetZaxis()->SetMaxDigits(3);

    an_corr_profile = new TProfile("Profile_anColl_corr", "Profilo Massa vs risoluzione cos#theta=1, risultati esatti", 25, 1, 4.5, -6, 6);
    an_corr_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_corr_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_corr_profile->SetStats(0);

    Resolution_an_mean = new TH2D("Resolution_anColl_mean", "risoluzione vs massa visibile cos#theta=1,  media soluzioni analitiche", 100, 1, 4.5, 300, -3, 1);
    Resolution_an_mean->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_mean->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_mean->GetZaxis()->SetTitle("Counts");
    Resolution_an_mean->SetStats(0);
    Resolution_an_mean->GetYaxis()->SetMaxDigits(1);
    Resolution_an_mean->GetZaxis()->SetMaxDigits(3);

    an_mean_profile = new TProfile("Profile_anColl_mean", "Profilo Massa vs risoluzione cos#theta=1, media soluzioni", 25, 1, 4.5, -6, 6);
    an_mean_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_mean_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_mean_profile->SetStats(0);

    Resolution_an_cos = new TH2D("Resolution_anColl_cos", "risoluzione vs massa visibile cos#theta=1,  cos#theta maggiore", 100, 1, 4.5, 300, -3, 1.5);
    Resolution_an_cos->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_cos->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_cos->GetZaxis()->SetTitle("Counts");
    Resolution_an_cos->SetStats(0);
    Resolution_an_cos->GetYaxis()->SetMaxDigits(1);
    Resolution_an_cos->GetZaxis()->SetMaxDigits(3);

    an_cos_profile = new TProfile("Profile_anColl_cos", "Profilo Massa vs risoluzione cos#theta=1,  cos#theta maggiore", 25, 1, 4.5, -6, 6);
    an_cos_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_cos_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_cos_profile->SetStats(0);

    Resolution_an_collcomp = new TH2D("Resolution_anColl_collcomp", "risoluzione vs massa visibile cos#theta=1,  coll comp", 100, 1, 4.5, 300, 0, 0.7);
    Resolution_an_collcomp->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_collcomp->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_collcomp->GetZaxis()->SetTitle("Counts");
    Resolution_an_collcomp->SetStats(0);
    Resolution_an_collcomp->GetYaxis()->SetMaxDigits(1);
    Resolution_an_collcomp->GetZaxis()->SetMaxDigits(3);

    an_collcomp_profile = new TProfile("Profile_anColl_collcomp", "Profilo Massa vs risoluzione cos#theta=1,  collcomp", 25, 1, 4.5, -3, 3);
    an_collcomp_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_collcomp_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_collcomp_profile->SetStats(0);

    Resolution_an_random = new TH2D("Resolution_anColl_random", "risoluzione vs massa visibile cos#theta=1,  random", 100, 1, 4.5, 300, -1.5, 1.5);
    Resolution_an_random->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_random->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_random->GetZaxis()->SetTitle("Counts");
    Resolution_an_random->SetStats(0);
    Resolution_an_random->GetYaxis()->SetMaxDigits(1);
    Resolution_an_random->GetZaxis()->SetMaxDigits(3);

    an_random_profile = new TProfile("Profile_anColl_random", "Profilo Massa vs risoluzione cos#theta=1,  random", 25, 1, 4.5, -3, 3);
    an_random_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_random_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_random_profile->SetStats(0);

    // inizializzo le funzioni per eventuali fit
    f_fit_corr1 = new TF1("f_anColl_corr_1", "pol4", 1.5, 4);
    // f_fit_corr2 = new TF1("f_anColl_corr_2", "pol1", 3.2, 4);

    f_fit_mean = new TF1("f_anColl_mean", "pol4", 1, 4.2);

    f_fit_cos = new TF1("f_anColl_cos", "pol8", 1, 4);

    f_fit_collcomp = new TF1("f_anColl_collcomp", "pol4", 1, 4);

    f_fit_random = new TF1("f_anColl_random", "pol4", 1, 4);

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
    h_residui_min = new TH1D("Hist_residui_AnColl_min", "residui percentuali analitica cos#theta=1 sol min (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_min->GetXaxis()->SetTitle("Residui");
    h_residui_min->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -3, stop = 1;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
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
    h_residui_corr = new TH1D("Hist_residui_AnColl_corr", "residui percentuali analitica cos#theta=1 posteriori (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_corr->GetXaxis()->SetTitle("Residui");
    h_residui_corr->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -1, stop = 1;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    h_residui_collcomp = new TH1D("Hist_residui_AnColl_collcomp", "residui percentuali analitica cos#theta=1 coll comp (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_collcomp->GetXaxis()->SetTitle("Residui");
    h_residui_collcomp->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -2, stop = 2;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    h_residui_random = new TH1D("Hist_residui_AnColl_random", "residui percentuali analitica cos#theta=1 random (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_random->GetXaxis()->SetTitle("Residui");
    h_residui_random->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());
}

ObjAnColl::~ObjAnColl()
{
    return;
}

void ObjAnColl::ComputeSolutions()
{
    Double_t a_coll = 4 * (pow(en_vis, 2) - tlv_visibile.P() * tlv_visibile.P());
    Double_t b_coll = -4 * tlv_visibile.T() * (vis_mass2 + tlv_Btag.M2());
    Double_t c_coll = 4 * pow(tlv_Btag.M() * tlv_visibile.P(), 2) + pow(tlv_Btag.M2() + vis_mass2, 2);
    sol_mag = Utilities::SolveEq2(a_coll, b_coll, c_coll, '+');
    sol_min = Utilities::SolveEq2(a_coll, b_coll, c_coll, '-');
    sol_mean = (sol_mag + sol_min) / 2;
}

void ObjAnColl::Accept(Visitor *v)
{
    v->Visit(this);
}

void ObjAnColl::PrintFinalStats()
{
    std::cout << "\nANALYTIC COLLINEAR STATISTICS:" << std::endl;
    std::cout << "Negative delta was founded in the " << n_delta_negativo * 100 / n_tot_accettabili << '%' << " of the events;" << std::endl;
    std::cout << "In this accepted events the cos(theta)> method is non resolutive for the " << n_inconcludente_cos * 100 / n_tot_accettabili << '%' << " of the events;\n"
              << std::endl;
}