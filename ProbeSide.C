#define ProbeSide_cxx
#include "ProbeSide.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

TH2D *MasRat, *EneRat;

void ProbeSide::Loop()
{
//   In a ROOT session, you can do:
//      root> .L ProbeSide.C
//      root> ProbeSide t
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
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   EneRat = new TH2D("EneRat","Esum / E B",50,0.76,1.01, 4,0,4);
   MasRat = new TH2D("MasRat","Mvis / M B",50,0.76,1.01, 4,0,4);
 
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      TLorentzVector tlv_sum = *tlv_cDec + *tlv_nuDec + *tlv_muDec ;
      double eRat = tlv_sum.E()/tlv_bDec->E() ;
      double mRat = tlv_sum.M()/tlv_bDec->M() ;
      EneRat->Fill( eRat, Rank-110 ) ;
      MasRat->Fill( mRat, Rank-110 ) ;
      // if (Cut(ientry) < 0) continue;
   }
}
