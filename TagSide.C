#define TagSide_cxx
#include "TagSide.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TAxis.h"

#include <string>
#include <iostream>

TagSide t; // lo definisco qua per non doverlo fare a mano ogni volta

TH1D *MassRatio;
TH2D *CosAlpha;
TH2D *T_Angle;
TH2D *Resolution;

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

   T_Angle = new TH2D("T_Angle", "(L/#sigma_{L},#alpha)", 100, 0, 100, 100, -0.001, 3.15);
   T_Angle->GetXaxis()->SetTitle("L/#sigma_{L}");
   T_Angle->GetYaxis()->SetTitle("#alpha");
   T_Angle->GetZaxis()->SetTitle("Counts");

   Resolution = new TH2D("Resolution", "risoluzione vs massa visibile", 100, 1, 4.5, 100, 0, 1);
   Resolution->GetXaxis()->SetTitle("massa visibile [GeV]");
   Resolution->GetYaxis()->SetTitle("risoluzione energia");
   Resolution->GetZaxis()->SetTitle("Counts");

   Long64_t nentries = fChain->GetEntriesFast();

   // variabili da usare nel ciclo for per evitare di doverle costruire e distruggere ogni volta
   // per facilitare la lettura verranno divise a gruppi e numerate
   //  1)
   Double_t visible_mass; // massa visibile
   Double_t ris_mass;     // risoluzione massa

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

      // cose che ho aggiunto io
      T_Angle->Fill(tlv_vertex->T(), alpha); // istogramma (L/sigma,angolo tra due direzioni)

      // risoluzione e massa visibile
      if (VtxCharge == 1)
      { // variabili 1)
         visible_mass = (*tlv_mumTag + *tlv_kapTag).M();
         ris_mass = (tlv_bTag->T() - (tlv_mumTag->T() + tlv_kapTag->T())) / tlv_bTag->T();
         Resolution->Fill(visible_mass, ris_mass);
      }
      if (VtxCharge == -1)
      { // variabili 1)
         visible_mass = (*tlv_mupTag + *tlv_kamTag).M();
         ris_mass = (tlv_bTag->T() - (tlv_mupTag->T() + tlv_kamTag->T())) / tlv_bTag->T();
         Resolution->Fill(visible_mass, ris_mass);
      }
   }
   std::cout << "completed without errors! :-)" << std::endl;
}
