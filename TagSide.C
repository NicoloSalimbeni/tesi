#define TagSide_cxx
#include "TagSide.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TAxis.h"
#include "TMath.h"
#include "TProfile.h"

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

TH1D *B_energy_res;
TProfile *En_profile;

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

   T_Angle = new TH2D("T_Angle", "(L/#sigma_{L},#alpha)", 100, 0, 100, 100, -0.001, 0.15);
   T_Angle->GetXaxis()->SetTitle("L/#sigma_{L}");
   T_Angle->GetYaxis()->SetTitle("#alpha");
   T_Angle->GetZaxis()->SetTitle("Counts");

   Resolution = new TH2D("Resolution", "risoluzione vs massa visibile", 100, 1, 4.5, 100, 0, 1);
   Resolution->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution->GetYaxis()->SetTitle("risoluzione energia");
   Resolution->GetZaxis()->SetTitle("Counts");

   En_profile = new TProfile("En_profile", "Profilo Massa vs risoluzione", 100, 1, 4.5, 0, 1);
   En_profile->GetXaxis()->SetTitle("massa visibile [GeV]");
   En_profile->GetYaxis()->SetTitle("risoluzione energia");

   B_energy_res = new TH1D("B_energy", "residui energia calcolata energia vera", 100, -200, 200);
   B_energy_res->GetXaxis()->SetTitle("Energia B [GeV]");
   B_energy_res->GetYaxis()->SetTitle("conteggi");

   Resolution_coll = new TH2D("Resolution_coll", "risoluzione vs massa visibile collinear", 100, 1, 4.5, 200, -1, 1);
   Resolution_coll->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_coll->GetYaxis()->SetTitle("risoluzione corretta energia");
   Resolution_coll->GetZaxis()->SetTitle("Counts");

   Resolution_imp_coll = new TH2D("Resolution_imp_coll", "risoluzione vs massa visibile improved collinear", 100, 1, 4.5, 200, -2, 0);
   Resolution_imp_coll->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_imp_coll->GetYaxis()->SetTitle("risoluzione corretta energia");
   Resolution_imp_coll->GetZaxis()->SetTitle("Counts");

   Resolution_non_coll = new TH2D("Resolution_non_coll", "risoluzione corretta vs massa visibile non collinear", 100, 1, 4.5, 200, -1, 1);
   Resolution_non_coll->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution_non_coll->GetYaxis()->SetTitle("risoluzione corretta energia");
   Resolution_non_coll->GetZaxis()->SetTitle("Counts");

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

      // risoluzione e massa visibile

      static Double_t ris_mass;

      // risoluzione normale
      ris_mass = (tlv_Btag.T() - tlv_visibile.T()) / tlv_Btag.T();
      Resolution->Fill(tlv_visibile.M(), ris_mass);
      En_profile->Fill(tlv_visibile.M(), ris_mass, 1);

      // risoluzione energia collineare
      static Double_t en_coll;
      static Double_t ris_coll;
      en_coll = tlv_visibile.T() * VtxMass / tlv_visibile.M();
      ris_coll = (tlv_Btag.T() - en_coll) / tlv_Btag.T();
      Resolution_coll->Fill(tlv_visibile.M(), ris_coll);

      // risoluzione improved collinear
      static Double_t en_imp_coll;
      static Double_t ris_imp_coll;

      en_imp_coll = (tlv_Btag.M2() + tlv_visibile.M2()) / (2 * tlv_visibile.T() - 2 * tlv_visibile.P());
      ris_imp_coll = (tlv_Btag.T() - en_imp_coll) / tlv_Btag.T();
      Resolution_imp_coll->Fill(tlv_visibile.M(), ris_imp_coll);

      // risoluzione non collinear
      static Double_t en_non_coll;
      static Double_t ris_non_coll;
      static Double_t pvz;

      pvz = (tlv_visibile.Vect().Dot(tlv_Btag.Vect())) / tlv_Btag.Vect().Mag();
      en_non_coll = (pow(tlv_Btag.M(), 2) + pow(tlv_visibile.M(), 2)) / (2 * tlv_visibile.T() - 2 * pvz);
      ris_non_coll = (tlv_Btag.T() - en_non_coll) / tlv_Btag.T();
      Resolution_non_coll->Fill(tlv_visibile.M(), ris_non_coll);

      // soluzione analitica FIXME non so come scegliere l'energia
      static Double_t a;
      static Double_t b;
      static Double_t c;
      static Double_t en;

      a = 4 * (pow(tlv_visibile.T(), 2) - pvz * pvz);
      b = -4 * tlv_visibile.T() * (tlv_visibile.M2() + tlv_Btag.M2());
      c = 4 * pow(tlv_Btag.M() * pvz, 2) + pow(tlv_Btag.M2() + tlv_visibile.M2(), 2);
      en = solve_eq2(a, b, c, tlv_visibile, pvz, tlv_Btag);

      if (en != -1 && pvz > 0)
      {
         B_energy_res->Fill(tlv_Btag.T() - en);
      }
   }
   std::cout << "completed without errors! :-)" << std::endl;
}
