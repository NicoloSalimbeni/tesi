//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jul  9 14:45:57 2022 by ROOT version 6.14/09
// from TTree ProbeSide/Small Data Tree Probe Side
// found on file: SmallNtuple.root
//////////////////////////////////////////////////////////

#ifndef ProbeSide_h
#define ProbeSide_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TLorentzVector.h"

class ProbeSide {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Rank;
   Int_t           bCode;
   TLorentzVector  *tlv_bDec;
   TLorentzVector  *tlv_cDec;
   TLorentzVector  *tlv_nuDec;
   TLorentzVector  *tlv_muDec;
   TLorentzVector  *tlv_muPrb;
   TLorentzVector  *tlv_vDec;

   // List of branches
   TBranch        *b_Rank;   //!
   TBranch        *b_bCode;   //!
   TBranch        *b_tlv_bDec;   //!
   TBranch        *b_tlv_cDec;   //!
   TBranch        *b_tlv_nuDec;   //!
   TBranch        *b_tlv_muDec;   //!
   TBranch        *b_tlv_muPrb;   //!
   TBranch        *b_tlv_vDec;   //!

   ProbeSide(TTree *tree=0);
   virtual ~ProbeSide();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ProbeSide_cxx
ProbeSide::ProbeSide(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("SmallNtuple.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("SmallNtuple.root");
      }
      f->GetObject("ProbeSide",tree);

   }
   Init(tree);
}

ProbeSide::~ProbeSide()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ProbeSide::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ProbeSide::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ProbeSide::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   tlv_bDec = 0;
   tlv_cDec = 0;
   tlv_nuDec = 0;
   tlv_muDec = 0;
   tlv_muPrb = 0;
   tlv_vDec = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Rank", &Rank, &b_Rank);
   fChain->SetBranchAddress("bCode", &bCode, &b_bCode);
   fChain->SetBranchAddress("tlv_bDec", &tlv_bDec, &b_tlv_bDec);
   fChain->SetBranchAddress("tlv_cDec", &tlv_cDec, &b_tlv_cDec);
   fChain->SetBranchAddress("tlv_nuDec", &tlv_nuDec, &b_tlv_nuDec);
   fChain->SetBranchAddress("tlv_muDec", &tlv_muDec, &b_tlv_muDec);
   fChain->SetBranchAddress("tlv_muPrb", &tlv_muPrb, &b_tlv_muPrb);
   fChain->SetBranchAddress("tlv_vDec", &tlv_vDec, &b_tlv_vDec);
   Notify();
}

Bool_t ProbeSide::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ProbeSide::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ProbeSide::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ProbeSide_cxx
