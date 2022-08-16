#include "ObjAnEs.h"
#include "TLorentzVector.h"
#include "TH2D.h"
#include "TProfile.h"
#include "../AnalysisUtilities/Utilities.h"
#include "../AnalysisFramework/Visitor.h"
#include "../AnalysisFramework/AnalysisSteering.h"
#include "../AnalysisFramework/AnalysisFactory.h"

class ObjAnEsFactory : public AnalysisFactory::AbsFactory
{
public:
    ObjAnEsFactory() : AnalysisFactory::AbsFactory("ObjAnEs"){};
    AnalysisObject *create() override
    {

        return new ObjAnEs();
    }
};

static ObjAnEsFactory AnEs_static_factory;

ObjAnEs::ObjAnEs()
{

    AnalysisSteering::subscribe(this);

    // tlb_Btag.M():-0.004 0      mass_B: -0.3 0.1;
    Resolution_an_mag = new TH2D("Resolution_anEs_mag", "risoluzione vs massa visibile,  metodo analitico soluzione maggiore", 100, 1, 4.5, 300, -0.004, 0);
    Resolution_an_mag->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_mag->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_mag->GetZaxis()->SetTitle("Counts");
    Resolution_an_mag->SetStats(0);
    Resolution_an_mag->GetYaxis()->SetMaxDigits(1);
    Resolution_an_mag->GetZaxis()->SetMaxDigits(3);

    // tlb_Btag.M(): 0 0.01      mass_B: -0.05 0.1;
    Resolution_an_min = new TH2D("Resolution_anEs_min", "risoluzione vs massa visibile,  metodo analitico soluzione minore", 100, 1, 4.5, 300, 0, 0.01);
    Resolution_an_min->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_min->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_min->GetZaxis()->SetTitle("Counts");
    Resolution_an_min->SetStats(0);
    Resolution_an_min->GetYaxis()->SetMaxDigits(1);
    Resolution_an_min->GetZaxis()->SetMaxDigits(3);

    // tlb_Btag.M(): -0.004 0.004      mass_B: -0.1 0.1;
    Resolution_an_corr = new TH2D("Resolution_anEs_corr", "risoluzione vs massa visibile,  risultati esatti", 100, 1, 4.5, 300, -0.004, 0.004);
    Resolution_an_corr->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_corr->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_corr->GetZaxis()->SetTitle("Counts");
    Resolution_an_corr->SetStats(0);
    Resolution_an_corr->GetYaxis()->SetMaxDigits(1);
    Resolution_an_corr->GetZaxis()->SetMaxDigits(3);

    an_corr_profile = new TProfile("Profile_anEs_corr", "Profilo Massa vs risoluzione, risultati esatti", 25, 1, 4, -3, 3);
    an_corr_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_corr_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_corr_profile->SetStats(0);

    // tlb_Btag.M():-1 1      mass_B: -0.1 0.8;
    Resolution_an_mean = new TH2D("Resolution_anEs_mean", "risoluzione vs massa visibile,  media soluzioni analitiche", 100, 1, 4.5, 300, -1, 1);
    Resolution_an_mean->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_mean->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_mean->GetZaxis()->SetTitle("Counts");
    Resolution_an_mean->SetStats(0);
    Resolution_an_mean->GetYaxis()->SetMaxDigits(1);
    Resolution_an_mean->GetZaxis()->SetMaxDigits(3);

    an_mean_profile = new TProfile("Profile_anEs_mean", "Profilo Massa vs risoluzione, media soluzioni", 25, 1, 4.5, -3, 3);
    an_mean_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_mean_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_mean_profile->SetStats(0);

    // tlb_Btag.M():-0.004 0.004      mass_B: -0.5 0.5;
    Resolution_an_cos = new TH2D("Resolution_anEs_cos", "risoluzione vs massa visibile,  cos#theta maggiore", 100, 1, 4.5, 300, -0.004, 0.004);
    Resolution_an_cos->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_cos->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_cos->GetZaxis()->SetTitle("Counts");
    Resolution_an_cos->SetStats(0);
    Resolution_an_cos->GetYaxis()->SetMaxDigits(1);
    Resolution_an_cos->GetZaxis()->SetMaxDigits(3);

    an_cos_profile = new TProfile("Profile_anEs_cos", "Profilo Massa vs risoluzione,  cos#theta maggiore", 25, 1, 4.5, -3, 3);
    an_cos_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_cos_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_cos_profile->SetStats(0);

    // tlb_Btag.M():-0.005 0.005      mass_B: -0.5 0.5;
    Resolution_an_collcomp = new TH2D("Resolution_anEs_collcomp", "risoluzione vs massa visibile,  coll comp", 100, 1, 4.5, 300, -0.005, 0);
    Resolution_an_collcomp->GetXaxis()->SetTitle("massa visibile [GeV]");
    Resolution_an_collcomp->GetYaxis()->SetTitle("risoluzione energia");
    Resolution_an_collcomp->GetZaxis()->SetTitle("Counts");
    Resolution_an_collcomp->SetStats(0);
    Resolution_an_collcomp->GetYaxis()->SetMaxDigits(1);
    Resolution_an_collcomp->GetZaxis()->SetMaxDigits(3);

    an_collcomp_profile = new TProfile("Profile_anEs_collcomp", "Profilo Massa vs risoluzione,  collcomp", 25, 1, 4.5, -3, 3);
    an_collcomp_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
    an_collcomp_profile->GetYaxis()->SetTitle("risoluzione energia");
    an_collcomp_profile->SetStats(0);

    // inizializzo le funzioni per eventuali fit
    f_fit_corr1 = new TF1("f_anEs_corr_1", "pol8", 1.5, 4);
    // f_fit_corr2 = new TF1("f_anEs_corr_2", "pol1", 3.2, 4);

    f_fit_mean = new TF1("f_anEs_mean", "pol4", 1, 4.2);

    f_fit_cos = new TF1("f_anEs_cos", "pol4", 1, 4);

    f_fit_collcomp = new TF1("f_anEs_collcomp", "pol4", 1, 4);

    // inizializzo istogrammi
    Int_t nbin = 100;
    Float_t start = -0.01, stop = 0.002; // tlb_Btag.M():      mass_B: -0.1 0.8;
    Float_t binwidth = (stop - start) / nbin;
    std::string s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);

    h_residui_mag = new TH1D("Hist_residui_AnEs_mag", "residui percentuali analitica sol mag (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_mag->GetXaxis()->SetTitle("Residui");
    h_residui_mag->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = 0, stop = 0.01; // tlb_Btag.M(): 0 0.01     mass_B: -0.1 0.8;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);
    h_residui_min = new TH1D("Hist_residui_AnEs_min", "residui percentuali analitica sol min (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_min->GetXaxis()->SetTitle("Residui");
    h_residui_min->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -2, stop = 0.8; // tlb_Btag.M(): -2 0.8     mass_B: -2 0.8;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);
    h_residui_mean = new TH1D("Hist_residui_AnEs_mean", "residui percentuali analitica media soluzioni (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_mean->GetXaxis()->SetTitle("Residui");
    h_residui_mean->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -0.01, stop = 0.01; // tlb_Btag.M(): -0.01 0.01      mass_B: -0.06 1;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);
    h_residui_cos = new TH1D("Hist_residui_AnEs_cos", "residui percentuali analitica cos#theta > (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_cos->GetXaxis()->SetTitle("Residui");
    h_residui_cos->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -0.01, stop = 0.01; // tlb_Btag.M(): -0.01 0.01      mass_B: -0.04 0.04;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);
    h_residui_corr = new TH1D("Hist_residui_AnEs_corr", "residui percentuali analitica posteriori (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_corr->GetXaxis()->SetTitle("Residui");
    h_residui_corr->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());

    nbin = 100;
    start = -0.05, stop = 0.005; // tlb_Btag.M():      mass_B: -0.2 0.2;
    binwidth = (stop - start) / nbin;
    s_binwidth = std::to_string(binwidth);
    s_binwidth.resize(5);
    h_residui_collcomp = new TH1D("Hist_residui_AnEs_collcomp", "residui percentuali analitica coll comp (E_{vera}-E_{stimata})/E_{vara}", nbin, start, stop);
    h_residui_collcomp->GetXaxis()->SetTitle("Residui");
    h_residui_collcomp->GetYaxis()->SetTitle(("Conteggi/" + s_binwidth).c_str());
}

ObjAnEs::~ObjAnEs()
{
    return;
}

void ObjAnEs::ComputeSolutions()
{
    Double_t pvz = (tlv_visibile.Vect().Dot(tlv_Btag.Vect())) / tlv_Btag.Vect().Mag();
    Double_t a = 4 * (pow(en_vis, 2) - pvz * pvz);
    Double_t b = -4 * en_vis * (vis_mass2 + tlv_Btag.M2());
    Double_t c = 4 * pow(tlv_Btag.M() * pvz, 2) + pow(tlv_Btag.M2() + vis_mass2, 2);
    sol_mag = Utilities::SolveEq2(a, b, c, '+');
    sol_min = Utilities::SolveEq2(a, b, c, '-');
    sol_mean = (sol_mag + sol_min) / 2;
}

void ObjAnEs::Accept(Visitor *v)
{
    v->Visit(this);
}

void ObjAnEs::PrintFinalStats()
{
    std::cout << "\nANALYTIC NON COLLINEAR STATISTICS:" << std::endl;
    std::cout << "Negative delta was founded in the " << n_delta_negativo * 100 / n_tot_accettabili << '%' << " of the events;" << std::endl;
    std::cout << "In this accepted events the cos(theta)> method is non resolutive for the " << n_inconcludente_cos * 100 / n_tot_accettabili << '%' << " of the events;\n"
              << std::endl;
}