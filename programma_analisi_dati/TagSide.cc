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
#include "TLorentzVector.h"

#include "./AnalysisUtilities/UtilitiesAnalysis.h"
#include "./AnalysisObjects/ObjAn.h"
#include "./AnalysisObjects/ObjColl.h"
#include "./AnalysisObjects/ObjImpColl.h"
#include "./AnalysisObjects/ObjNonColl.h"
#include "./AnalysisFramework/Dispatcher.h"

#include <string>
#include <iostream>
TagSide t;

Double_t vis_mass;
Double_t vis_mass2;
Double_t pvz;

UtilitiesAnalysis *util = new UtilitiesAnalysis();

ObjAn *an_analitica = new ObjAn();
ObjColl *an_coll = new ObjColl();
ObjImpColl *an_impcoll = new ObjImpColl();
ObjNonColl *an_noncoll = new ObjNonColl();

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

      //=====================COSE CHE HO AGGIUNTO IO===============================================

      TLorentzVector tlv_visibile;
      if (VtxCharge == 1)
      {
         tlv_visibile = *tlv_mumTag + *tlv_kapTag;
      }
      if (VtxCharge == -1)
      {
         tlv_visibile = *tlv_mupTag + *tlv_kamTag;
      }
      util->Update(tlv_Btag, tlv_visibile);
      Dispatcher::Notify(tlv_Btag, tlv_visibile);
   }
   std::cout << "completed without errors! :-)" << std::endl;
}