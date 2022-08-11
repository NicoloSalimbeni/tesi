//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jul  9 13:03:36 2022 by ROOT version 6.14/09
// from TTree TagSide/Small Data Tree Tag Side
// found on file: SmallNtuple.root
//////////////////////////////////////////////////////////

#ifndef TagSide_h
#define TagSide_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TLorentzVector.h"

#include <string>

class TagSide
{
public:
   TTree *fChain;  //! pointer to the analyzed TTree or TChain
   Int_t fCurrent; //! current Tree number in a TChain

   // Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t EventNumber;
   TLorentzVector *tlv_bTag;
   Int_t VtxCharge;
   Float_t VtxMass;
   TLorentzVector *tlv_vertex;
   TLorentzVector *tlv_mupTag;
   TLorentzVector *tlv_mumTag;
   TLorentzVector *tlv_kapTag;
   TLorentzVector *tlv_kamTag;
   //   Int_t           EventNumber;

   // List of branches
   //   TBranch        *b_EventNumber;   //!
   TBranch *b_tlv_bTag;    //!
   TBranch *b_VtxCharge;   //!
   TBranch *b_VtxMass;     //!
   TBranch *b_tlv_vertex;  //!
   TBranch *b_tlv_mupTag;  //!
   TBranch *b_tlv_mumTag;  //!
   TBranch *b_tlv_kapTag;  //!
   TBranch *b_tlv_kamTag;  //!
   TBranch *b_EventNumber; //!

   TagSide(TTree *tree = 0);
   virtual ~TagSide();
   virtual Int_t Cut(Long64_t entry);
   virtual Int_t GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void Init(TTree *tree);
   virtual void Loop(std::string dump = "no");
   virtual Bool_t Notify();
   virtual void Show(Long64_t entry = -1);
};

#endif

#ifdef TagSide_cxx
TagSide::TagSide(TTree *tree) : fChain(0)
{
   // if parameter tree is not specified (or zero), connect the file
   // used to generate this class and read the Tree.
   if (tree == 0)
   {
      TFile *f = (TFile *)gROOT->GetListOfFiles()->FindObject("SmallNtuple.root");
      if (!f || !f->IsOpen())
      {
         f = new TFile("SmallNtuple.root");
      }
      f->GetObject("TagSide", tree);
   }
   Init(tree);
}

TagSide::~TagSide()
{
   if (!fChain)
      return;
   delete fChain->GetCurrentFile();
}

Int_t TagSide::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain)
      return 0;
   return fChain->GetEntry(entry);
}
Long64_t TagSide::LoadTree(Long64_t entry)
{
   // Set the environment to read one entry
   if (!fChain)
      return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0)
      return centry;
   if (fChain->GetTreeNumber() != fCurrent)
   {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TagSide::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   tlv_bTag = 0;
   tlv_vertex = 0;
   tlv_mupTag = 0;
   tlv_mumTag = 0;
   tlv_kapTag = 0;
   tlv_kamTag = 0;
   // Set branch addresses and branch pointers
   if (!tree)
      return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   //    fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("tlv_bTag", &tlv_bTag, &b_tlv_bTag);
   fChain->SetBranchAddress("VtxCharge", &VtxCharge, &b_VtxCharge);
   fChain->SetBranchAddress("VtxMass", &VtxMass, &b_VtxMass);
   fChain->SetBranchAddress("tlv_vertex", &tlv_vertex, &b_tlv_vertex);
   fChain->SetBranchAddress("tlv_mupTag", &tlv_mupTag, &b_tlv_mupTag);
   fChain->SetBranchAddress("tlv_mumTag", &tlv_mumTag, &b_tlv_mumTag);
   fChain->SetBranchAddress("tlv_kapTag", &tlv_kapTag, &b_tlv_kapTag);
   fChain->SetBranchAddress("tlv_kamTag", &tlv_kamTag, &b_tlv_kamTag);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   Notify();
}

Bool_t TagSide::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TagSide::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain)
      return;
   fChain->Show(entry);
}
Int_t TagSide::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   return 1;
}
#endif // #ifdef TagSide_cxx
