#define TagSide_cxx
#include "TagSide.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TAxis.h"
#include "TMath.h"
#include "TProfile.h"
#include "TF1.h"
#include "TFitResult.h"

#include "./utilities.cc"

#include <string>
#include <iostream>

TagSide t; // lo definisco qua per non doverlo fare a mano ogni volta

TH1D *MassRatio;
TH2D *CosAlpha;
TH2D *T_Angle;

TH2D *Resolution;
TH2D *Resolution_coll;
TH2D *Resolution_imp_coll;
TH2D *Resolution_non_coll;
TH2D *Resolution_an_mag;
TH2D *Resolution_an_min;
TH2D *Resolution_an_cos;
TH2D *Resolution_an_mean;
TH2D *Resolution_an_corr;

TH1D *B_energy_res;
TProfile *En_profile;
TProfile *coll_profile;
TProfile *imp_coll_profile;
TProfile *non_coll_profile;
TProfile *an_mean_profile;
TProfile *an_corr_profile;
TProfile *an_cos_profile;

extern Double_t sol_mag; // definiti in utilities.cc
extern Double_t sol_min;

void TagSide::Loop(std::string dump)
{
   //   In a ROOT session, you can do:
   //      root> .L TagSide.C
   //      root> TagSide t
   //      root> t.GetEntry(12); // Fill t data members with entry number 12
   //      root> t.Show();       // Show values of entry 12
   //      root> t.Show(16);     // Read and show values of entry 16
   //      root> t.Loop();       // Loop on all entries
   //

   //     This is the loop skeleton where:
   //    jentry is the global entry number in the chain
   //    ientry is the entry number in the current Tree
   //  Note that the argument to GetEntry must be:
   //    jentry for TChain::GetEntry
   //    ientry for TTree::GetEntry and TBranch::GetEntry
   //
   //       To read only selected branches, Insert statements like:
   // METHOD1:
   //    fChain->SetBranchStatus("*",0);  // disable all branches
   //    fChain->SetBranchStatus("branchname",1);  // activate branchname
   // METHOD2: replace line
   //    fChain->GetEntry(jentry);       //read all branches
   // by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0)
      return;

   // book histograms
   MassRatio = new TH1D("MassRatio", " 1-M(sum)/M(const)", 100, -0.2, 0.2);
   CosAlpha = new TH2D("CosAlpha", "Cos-angle vs L ", 50, 0., 25., 50, 0.901, 1.001);

   T_Angle = new TH2D("T_Angle", "(L/#sigma_{L},#alpha)", 100, 0, 100, 100, 0, 0.10);
   T_Angle->GetXaxis()->SetTitle("L/#sigma_{L}");
   T_Angle->GetYaxis()->SetTitle("#alpha");
   T_Angle->GetZaxis()->SetTitle("Counts");
   T_Angle->SetStats(0);
   T_Angle->GetZaxis()->SetMaxDigits(3);

   Resolution = new TH2D("Resolution", "risoluzione vs massa visibile", 100, 1, 4.5, 100, 0, 1);
   Resolution->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution->GetYaxis()->SetTitle("risoluzione energia");
   Resolution->GetZaxis()->SetTitle("Counts");

   En_profile = new TProfile("En_profile", "Profilo Massa vs risoluzione", 100, 1, 4.5, 0, 1);
   En_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
   En_profile->GetYaxis()->SetTitle("risoluzione energia");

   B_energy_res = new TH1D("B_energy", "residui energia calcolata energia vera", 100, -2, 2);
   B_energy_res->GetXaxis()->SetTitle("residui energia B [GeV]");
   B_energy_res->GetYaxis()->SetTitle("conteggi");

   Resolution_coll = new TH2D("Resolution_coll", "risoluzione vs massa visibile collinear", 100, 1, 4.5, 300, -3, 1);
   Resolution_coll->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_coll->GetYaxis()->SetTitle("risoluzione energia");
   Resolution_coll->GetZaxis()->SetTitle("Counts");
   Resolution_coll->SetStats(0);
   Resolution_coll->GetZaxis()->SetMaxDigits(3);

   coll_profile = new TProfile("Profile_coll", "Profilo Massa vs risoluzione collinear", 25, 1, 4.5, -3, 1);
   coll_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
   coll_profile->GetYaxis()->SetTitle("risoluzione energia");
   coll_profile->SetStats(0);

   Resolution_imp_coll = new TH2D("Resolution_imp_coll", "risoluzione vs massa visibile improved collinear", 100, 1, 4.5, 300, -3, 1);
   Resolution_imp_coll->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_imp_coll->GetYaxis()->SetTitle("risoluzione energia");
   Resolution_imp_coll->GetZaxis()->SetTitle("Counts");
   Resolution_imp_coll->SetStats(0);
   Resolution_imp_coll->GetZaxis()->SetMaxDigits(3);

   imp_coll_profile = new TProfile("Profile_imp_coll", "Profilo Massa vs risoluzione improved collinear", 25, 1, 4.5, -3, 1);
   imp_coll_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
   imp_coll_profile->GetYaxis()->SetTitle("risoluzione energia");
   imp_coll_profile->SetStats(0);

   Resolution_non_coll = new TH2D("Resolution_non_coll", "risoluzione vs massa visibile non collinear", 100, 1, 4.5, 300, -3, 1);
   Resolution_non_coll->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_non_coll->GetYaxis()->SetTitle("risoluzione energia");
   Resolution_non_coll->GetZaxis()->SetTitle("Counts");
   Resolution_non_coll->SetStats(0);
   Resolution_non_coll->GetZaxis()->SetMaxDigits(3);

   non_coll_profile = new TProfile("Profile_non_coll", "Profilo Massa vs risoluzione non collinear", 25, 1, 4.5, -3, 1);
   non_coll_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
   non_coll_profile->GetYaxis()->SetTitle("risoluzione energia");
   non_coll_profile->SetStats(0);

   Resolution_an_mag = new TH2D("Resolution_an_mag", "risoluzione vs massa visibile,  metodo analitico soluzione maggiore", 100, 1, 4.5, 300, -0.004, 0);
   Resolution_an_mag->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_an_mag->GetYaxis()->SetTitle("risoluzione energia");
   Resolution_an_mag->GetZaxis()->SetTitle("Counts");
   Resolution_an_mag->SetStats(0);
   Resolution_an_mag->GetYaxis()->SetMaxDigits(1);
   Resolution_an_mag->GetZaxis()->SetMaxDigits(3);

   Resolution_an_min = new TH2D("Resolution_an_min", "risoluzione vs massa visibile,  metodo analitico soluzione minore", 100, 1, 4.5, 300, 0, 0.01);
   Resolution_an_min->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_an_min->GetYaxis()->SetTitle("risoluzione energia");
   Resolution_an_min->GetZaxis()->SetTitle("Counts");
   Resolution_an_min->SetStats(0);
   Resolution_an_min->GetYaxis()->SetMaxDigits(1);
   Resolution_an_min->GetZaxis()->SetMaxDigits(3);

   Resolution_an_corr = new TH2D("Resolution_an_corr", "risoluzione vs massa visibile,  risultati esatti", 100, 1, 4.5, 300, -0.004, 0.004);
   Resolution_an_corr->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_an_corr->GetYaxis()->SetTitle("risoluzione energia");
   Resolution_an_corr->GetZaxis()->SetTitle("Counts");
   Resolution_an_corr->SetStats(0);
   Resolution_an_corr->GetYaxis()->SetMaxDigits(1);
   Resolution_an_corr->GetZaxis()->SetMaxDigits(3);

   an_corr_profile = new TProfile("Profile_an_corr", "Profilo Massa vs risoluzione, risultati esatti", 25, 1, 4.5, -3, 1);
   an_corr_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
   an_corr_profile->GetYaxis()->SetTitle("risoluzione energia");
   an_corr_profile->SetStats(0);

   Resolution_an_mean = new TH2D("Resolution_an_mean", "risoluzione vs massa visibile,  media soluzioni analitiche", 100, 1, 4.5, 300, -1, 1);
   Resolution_an_mean->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_an_mean->GetYaxis()->SetTitle("risoluzione energia");
   Resolution_an_mean->GetZaxis()->SetTitle("Counts");
   Resolution_an_mean->SetStats(0);
   Resolution_an_mean->GetYaxis()->SetMaxDigits(1);
   Resolution_an_mean->GetZaxis()->SetMaxDigits(3);

   an_mean_profile = new TProfile("Profile_an_mean", "Profilo Massa vs risoluzione, media soluzioni", 25, 1, 4.5, -3, 1);
   an_mean_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
   an_mean_profile->GetYaxis()->SetTitle("risoluzione energia");
   an_mean_profile->SetStats(0);

   Resolution_an_cos = new TH2D("Resolution_an_cos", "risoluzione vs massa visibile,  cos#theta maggiore", 100, 1, 4.5, 300, -0.004, 0.004);
   Resolution_an_cos->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_an_cos->GetYaxis()->SetTitle("risoluzione energia");
   Resolution_an_cos->GetZaxis()->SetTitle("Counts");
   Resolution_an_cos->SetStats(0);
   Resolution_an_cos->GetYaxis()->SetMaxDigits(1);
   Resolution_an_cos->GetZaxis()->SetMaxDigits(3);

   an_cos_profile = new TProfile("Profile_an_cos", "Profilo Massa vs risoluzione,  cos#theta maggiore", 25, 1, 4.5, -3, 1);
   an_cos_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
   an_cos_profile->GetYaxis()->SetTitle("risoluzione energia");
   an_cos_profile->SetStats(0);

   Long64_t nentries = fChain->GetEntriesFast();

   std::cout << "Analysis started, wait...\t" << std::flush;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry = 0; jentry < nentries; jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0)
         break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      TLorentzVector tlv_Btag = *tlv_mupTag + *tlv_mumTag + *tlv_kapTag + *tlv_kamTag;
      if (dump == "yes")
      {
         std::cout << " at event " << jentry << "  " << VtxCharge << " " << VtxMass << " " << tlv_Btag.M() << std::endl;
      }
      if (VtxMass > 0)
         MassRatio->Fill(1 - tlv_Btag.M() / VtxMass);
      double alpha = tlv_Btag.Angle(tlv_vertex->Vect());
      CosAlpha->Fill(tlv_vertex->T(), cos(alpha));

      //=====================COSE CHE HO AGGIUNTO IO===============================================
      T_Angle->Fill(tlv_vertex->T(), alpha); // istogramma (L/sigma,angolo tra due direzioni)

      TLorentzVector tlv_visibile;
      if (VtxCharge == 1)
      {
         tlv_visibile = *tlv_mumTag + *tlv_kapTag;
      }
      if (VtxCharge == -1)
      {
         tlv_visibile = *tlv_mupTag + *tlv_kamTag;
      }

      static Double_t vis_mass;
      static Double_t vis_mass2;
      vis_mass = tlv_visibile.M();
      vis_mass2 = tlv_visibile.M2();

      // RISOLUZIONE

      // risoluzione normale
      static Double_t ris_mass;
      ris_mass = (tlv_Btag.T() - tlv_visibile.T()) / tlv_Btag.T();
      Resolution->Fill(vis_mass, ris_mass);
      En_profile->Fill(vis_mass, ris_mass, 1);

      // risoluzione energia collineare
      static Double_t en_coll;
      static Double_t ris_coll;
      en_coll = tlv_visibile.T() * VtxMass / vis_mass;
      ris_coll = (tlv_Btag.T() - en_coll) / tlv_Btag.T();
      Resolution_coll->Fill(vis_mass, ris_coll);
      coll_profile->Fill(vis_mass, ris_coll, 1);

      // risoluzione improved collinear
      static Double_t en_imp_coll;
      static Double_t ris_imp_coll;

      en_imp_coll = (tlv_Btag.M2() + vis_mass2) * (tlv_visibile.T() + tlv_visibile.P()) / (2 * vis_mass2);
      ris_imp_coll = (tlv_Btag.T() - en_imp_coll) / tlv_Btag.T();
      Resolution_imp_coll->Fill(vis_mass, ris_imp_coll);
      imp_coll_profile->Fill(vis_mass, ris_imp_coll, 1);

      // risoluzione non collinear
      static Double_t en_non_coll;
      static Double_t ris_non_coll;
      static Double_t pvz;

      pvz = (tlv_visibile.Vect().Dot(tlv_Btag.Vect())) / tlv_Btag.Vect().Mag();
      en_non_coll = (pow(tlv_Btag.M(), 2) + pow(vis_mass, 2)) / (2 * tlv_visibile.T() - 2 * pvz);
      ris_non_coll = (tlv_Btag.T() - en_non_coll) / tlv_Btag.T();
      Resolution_non_coll->Fill(vis_mass, ris_non_coll);
      non_coll_profile->Fill(vis_mass, ris_non_coll, 1);

      // FIXME soluzione analitica non so come scegliere l'energia
      static Double_t a;
      static Double_t b;
      static Double_t c;

      a = 4 * (pow(tlv_visibile.T(), 2) - pvz * pvz);
      b = -4 * tlv_visibile.T() * (vis_mass2 + tlv_Btag.M2());
      c = 4 * pow(tlv_Btag.M() * pvz, 2) + pow(tlv_Btag.M2() + vis_mass2, 2);

      // soluzione analitica scelta con il coseno maggiore
      static Double_t en_cos;
      en_cos = solve_eq2(a, b, c, tlv_visibile, pvz, tlv_Btag, 'c');
      static Double_t res_an_cos;
      res_an_cos = (tlv_Btag.T() - en_cos) / tlv_Btag.T();
      Resolution_an_cos->Fill(vis_mass, res_an_cos);
      an_cos_profile->Fill(vis_mass, res_an_cos, 1);

      // entrambe le soluzioni con maggiore e minore
      Resolution_an_min->Fill(vis_mass, (tlv_Btag.T() - sol_min) / tlv_Btag.T());
      Resolution_an_mag->Fill(vis_mass, (tlv_Btag.T() - sol_mag) / tlv_Btag.T());

      // media delle soluzioni analitiche
      static Double_t sol_mean;
      static Double_t ris_an_mean;
      sol_mean = (sol_mag + sol_min) / 2;
      ris_an_mean = (tlv_Btag.T() - sol_mean) / tlv_Btag.T();
      Resolution_an_mean->Fill(vis_mass, ris_an_mean);
      an_mean_profile->Fill(vis_mass, ris_an_mean, 1);

      // studio della soluzione scelta a posteriori
      static Double_t en_corr;
      en_corr = solve_eq2(a, b, c, tlv_visibile, pvz, tlv_Btag, 'i');
      static Double_t ris_an_corr;
      ris_an_corr = (tlv_Btag.T() - en_corr) / tlv_Btag.T();
      Resolution_an_corr->Fill(vis_mass, ris_an_corr);
      an_corr_profile->Fill(vis_mass, ris_an_corr, 1);

      if (en_corr != -1)
      {
         B_energy_res->Fill((tlv_Btag.T() - en_corr) / tlv_Btag.T());
      }
   }
   std::cout << "completed without errors! :-)" << std::endl;

   //=============FIT TPROFILE======================

   TFile *file_fit_profile = new TFile("./analisi_risoluzione_energia/file_fit_profile.root", "RECREATE");
   file_fit_profile->cd();

   TF1 *f_an_corr_1 = new TF1("f_an_corr_1", "pol1", 1.5, 3.2);
   TF1 *f_an_corr_2 = new TF1("f_an_corr_2", "pol1", 3.2, 4);
   TFitResultPtr fit_res_an_corr_1 = an_corr_profile->Fit(f_an_corr_1, "SR");
   TFitResultPtr fit_res_an_corr_2 = an_corr_profile->Fit(f_an_corr_2, "SR+");
   fit_res_an_corr_1->SetNameTitle("fit_res_an_corr_1", "pol1");
   fit_res_an_corr_2->SetNameTitle("fit_res_an_corr_2", "pol1");
   fit_res_an_corr_1->Write();
   fit_res_an_corr_2->Write();

   TF1 *f_an_mean = new TF1("f_an_mean", "pol4", 1, 4.2);
   TFitResultPtr fit_res_an_mean = an_mean_profile->Fit(f_an_mean, "SR");
   fit_res_an_mean->SetNameTitle("fit_res_an_mean", "pol4");
   fit_res_an_mean->Write();

   TF1 *f_an_cos = new TF1("f_an_cos", "pol4", 1, 4);
   TFitResultPtr fit_res_an_cos = an_cos_profile->Fit(f_an_mean, "SR");
   fit_res_an_cos->SetNameTitle("fit_res_an_cos", "pol4");
   fit_res_an_cos->Write();

   TF1 *f_coll = new TF1("f_coll", "pol4", 1, 4.2);
   TFitResultPtr fit_res_coll = coll_profile->Fit(f_coll, "SR");
   fit_res_coll->SetNameTitle("fit_res_coll", "pol4");
   fit_res_coll->Write();

   TF1 *f_imp_coll = new TF1("f_imp_coll", "pol4", 1, 4.2);
   TFitResultPtr fit_res_imp_coll = imp_coll_profile->Fit(f_imp_coll, "SR");
   fit_res_imp_coll->SetNameTitle("fit_res_imp_coll", "pol4");
   fit_res_imp_coll->Write();

   TF1 *f_non_coll = new TF1("f_non_coll", "pol4", 1, 4.2);
   TFitResultPtr fit_res_non_coll = non_coll_profile->Fit(f_non_coll, "SR");
   fit_res_non_coll->SetNameTitle("fit_res_non_coll", "pol4");
   fit_res_non_coll->Write();

   file_fit_profile->Close();
   // ============ salvo i png ======================
   TCanvas *c = new TCanvas("c", "c", 900, 650);
   c->cd();

   // salvo le risoluzioni
   Resolution_coll->Draw("CONT4Z");
   c->SaveAs("./analisi_risoluzione_energia/collinear/Resolution_coll.png");
   Resolution_imp_coll->Draw("CONT4Z");
   c->SaveAs("./analisi_risoluzione_energia/improved_collinear/Resolution_imp_coll.png");
   Resolution_non_coll->Draw("CONT4Z");
   c->SaveAs("./analisi_risoluzione_energia/non_collinear/Resolution_non_coll.png");
   Resolution_an_min->Draw("CONT4Z");
   c->SaveAs("./analisi_risoluzione_energia/analitica/Resolution_an_min.png");
   Resolution_an_mag->Draw("CONT4Z");
   c->SaveAs("./analisi_risoluzione_energia/analitica/Resolution_an_mag.png");
   Resolution_an_corr->Draw("CONT4Z");
   c->SaveAs("./analisi_risoluzione_energia/analitica/Resolution_an_corr.png");
   Resolution_an_mean->Draw("CONT4Z");
   c->SaveAs("./analisi_risoluzione_energia/analitica/Resolution_an_mean.png");
   Resolution_an_cos->Draw("CONT4Z");
   c->SaveAs("./analisi_risoluzione_energia/analitica/Resolution_an_cos.png");

   // salvo i profili
   coll_profile->Draw();
   c->SaveAs("./analisi_risoluzione_energia/collinear/Profile_coll.png");
   imp_coll_profile->Draw();
   c->SaveAs("./analisi_risoluzione_energia/improved_collinear/Profile_imp_coll.png");
   non_coll_profile->Draw();
   c->SaveAs("./analisi_risoluzione_energia/non_collinear/Profile_non_coll.png");
   an_corr_profile->Draw();
   c->SaveAs("./analisi_risoluzione_energia/analitica/Profile_an_corr.png");
   an_mean_profile->Draw();
   c->SaveAs("./analisi_risoluzione_energia/analitica/Profile_an_mean.png");
   an_cos_profile->Draw();
   c->SaveAs("./analisi_risoluzione_energia/analitica/Profile_an_cos.png");

   // salvo l'angolo
   T_Angle->Draw("CONT4Z");
   c->SaveAs("./analisi_angolo/Distribuzione_angolo.png");

   // salvo nel TFile
   TFile *f = new TFile("grafici.root", "UPDATE");
   f->cd();

   f->Delete("Resolution_coll;*");
   f->Delete("Resolution_imp_coll;*");
   f->Delete("Resolution_non_coll;*");
   f->Delete("Resolution_an_mag;*");
   f->Delete("Resolution_an_min;*");
   f->Delete("Resolution_an_cos;*");

   f->Delete("Profile_coll;*");
   f->Delete("Profile_imp_coll;*");
   f->Delete("Profile_non_coll;*");
   f->Delete("Profile_an_corr;*");
   f->Delete("Profile_an_mean;*");
   f->Delete("Profile_an_cos;*");

   f->Delete("MassRatio;*");
   f->Delete("CosAlpha;*");
   f->Delete("T_Angle;*");

   Resolution_coll->Write();
   Resolution_imp_coll->Write();
   Resolution_non_coll->Write();
   Resolution_an_min->Write();
   Resolution_an_mag->Write();
   Resolution_an_corr->Write();
   Resolution_an_mean->Write();

   coll_profile->Write();
   imp_coll_profile->Write();
   non_coll_profile->Write();

   MassRatio->Write();
   CosAlpha->Write();
   T_Angle->Write();
}
