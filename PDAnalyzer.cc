// PDAnalyzer class to process a ntuple entry and return a true/false flag:
//     - when writing the ntuple the flag is used to actually write
//       the entry on the ROOT file, for traditional flat ntuples, or 
//       put the informations inside the Event for EDM ntuples or NANOAOD;
//     - when reading the ntuple the value is used just to count events;
//     - the value can be used to skim the ntuple.
//
// Another PDAnalyzerUtil class is also provided, for the following purposes:
//     - use configuration parameters to choose which blocks are actually 
//       to be read, see the corresponding code files for an example;
//     - provide any utility function tightly bound to the ntuple format,
//       e.g. to navigate through indices, compute complex quantites from
//       basic ones and so on.

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

#include "PDAnalyzer.h"

#include "TDirectory.h"
#include "TBranch.h"
#include "TTree.h"
#include "TFile.h"
//#include "TCanvas.h"
#include "Math/LorentzVector.h"
#include "TLorentzVector.h"

// additional features
//#include "DataSetFilter.cc" // dataset filter

using namespace std;

// Code lines to skim ntuple and/or produce a reduced ntuple are
// activated/deactivated by the preprocessor
// macros "SKIM_NTUPLE" and "REDUCE_NTUPLE" respectively;
// they're set in the header file.
// Macros are used just to flag the relevant code lines, 
// normally the code would not make use of the preprocessor for this.

#if REDUCE_NTUPLE != 0
#include "PDReducedNtupleWriter.h" // reduced ntuple
#endif

// ===========================================================================
// FS 2022: Ntuple contents

TFile *fSmallNtuple ;
TTree *TagSide, *ProbeSide  ;
int EventNumber ;
int VtxCharge;
float VtxMass ;
TLorentzVector *tlv_bTag, *tlv_mupTag, *tlv_mumTag , *tlv_kapTag, *tlv_kamTag, *tlv_vertex; 
TLorentzVector *tlv_bDec, *tlv_vDec, *tlv_muDec, *tlv_nuDec, *tlv_cDec, *tlv_muPrb;
int Rank, bCode ;

enum LundId 
  {   LuEle = 11, LuNue = 12, LuMuo = 13, LuNum = 14, LuGam = 22, 
      LuPip = 211, LuKap = 321, LuKs0 = 311, LuPrt = 2214,
      LuDpl = 411, LuDzr = 421, LuDs  = 431,
      LuDstp= 413, LuDst0= 423, LuDsst= 433,
      LuBzr = 511, LuBpl = 521, LuBs  = 531,
      LuJPsi= 443, LuPhi = 333
  }; // Lund Codes

const int nBpSml(4), nBzSml(4), nBsSml(4);

int ListBpDzMuNu[] { LundId::LuBpl, -LuDzr, LundId::LuNum, -LundId::LuMuo } ;
int ListBzDpMuNu[] { LundId::LuBzr, -LuDpl, LundId::LuNum, -LundId::LuMuo } ;
int ListBsDsMuNu[] { LundId::LuBs , -LuDs , LundId::LuNum, -LundId::LuMuo } ;

PDAnalyzer::PDAnalyzer() {

  std::cout << "new PDAnalyzer" << std::endl;

  // User parameters are set as names associated to a string:
  //     - numeric values are converted internally as strings;
  //     - default values can be set in the analyzer class constructor,
  //       values can be given as strings, also for numerical values;
  //     - default values can be set also in the TMPAnalyzerUtil constructor,
  //       the ones in TMPAnalyzer constructor override the ones in 
  //       TMPAnalyzerUtil .

  setUserParameter( "verbose", "f" );
  setUserParameter( "ptCut", "40.0" );

}

PDAnalyzer::~PDAnalyzer() {}

void PDAnalyzer::beginJob() {

  PDAnalyzerUtil::beginJob();

  // User parameters are retrieved as strings by using their names;
  // numeric parameters ( int, float or whatever ) can be directly set
  // by passing the corresponding variable, e.g.:
  //   getUserParameter( "name", x );
  // or secifying the type as a template parameter, e.g.
  //   i = getUserParameter<int>( "name" );

  getUserParameter( "verbose", verbose );
  getUserParameter( "ptCut", ptCut );
// alternatively:
//  verbose = getUserParameter<bool> ( "verbose" );
//  ptCut   = getUserParameter<float>( "ptCut"   );

#if SKIM_NTUPLE != 0
  dropBranch( "jet*" ); // drop some branch from the skimmed ntuple,
                        // if required, a limited support for wild characters
                        // is provided
  initWSkim( new TFile( "skim.root", "RECREATE" ) ); // open a file for 
                                                     // the skimmed ntuple
#endif

#if REDUCE_NTUPLE != 0
  rWriter = new PDReducedNtupleWriter;           // create reduced ntuple
  rWriter->open( "reducedNtu.root", "RECREATE" ); // open file
                                                  // for reduced ntuple
#endif

// additional features
//  DataSetFilter::beginJob(); // dataset filter

  // ============================================================================
  // FS, June 2022;
  nFound = 0 ;
  return;

}


void PDAnalyzer::book() {

  // putting "autoSavedObject" in front of the histo creation 
  // it's automatically marked for saving on file; the option 
  // is uneffective when not using the full utility

  autoSavedObject =
  hptmumax        = new TH1D( "hptmumax"    , "ptmumax"    ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmu2nd        = new TH1D( "hptmu2nd"    , "ptmu 2nd"   ,  50, 0.0, 100.0 );
  autoSavedObject =
  hptmu           = new TH1D( "hptmu"       , "ptmu"       ,  50, 0.0, 100.0 );
  autoSavedObject =
  hMass1          = new TH1F( "hMass1"      , "mass"       , 120, 0.0,   6.0 );
  autoSavedObject =
  hMass2          = new TH1F( "hMass2"      , "mass"       , 600, 0.0,   6.0 );
  autoSavedObject =
  hMass3          = new TH1F( "hMass3"      , "mass"       , 600, 0.0,   6.0 );

  autoSavedObject = dPtVsdR = new TH2D("dPtVsdR", "dPtVsdR",100,0.,0.5,50,-0.5,0.5) ;

  // =========================================================================
  // FS June 2022 : produce small ntuple
  fSmallNtuple= new TFile("SmallNtuple.root","recreate") ;

  tlv_bTag = new TLorentzVector(0,0,0,0);
  tlv_bDec = new TLorentzVector(0,0,0,0);
  tlv_cDec = new TLorentzVector(0,0,0,0);
  tlv_muDec = new TLorentzVector(0,0,0,0);
  tlv_nuDec = new TLorentzVector(0,0,0,0);
  tlv_muPrb = new TLorentzVector(0,0,0,0);
  tlv_vDec = new TLorentzVector(0,0,0,0);
  tlv_mupTag = new TLorentzVector(0,0,0,0);
  tlv_mumTag = new TLorentzVector(0,0,0,0);
  tlv_kapTag = new TLorentzVector(0,0,0,0);
  tlv_kamTag = new TLorentzVector(0,0,0,0);
  tlv_vertex = new TLorentzVector(0,0,0,0);

  // myTree->Branch("tlv_mPrb","TLorentzVector",&tlv_mPrb) ;

  TagSide = new TTree("TagSide","Small Data Tree Tag Side") ;
  TagSide->Branch("EventNumber",&EventNumber,"EventNumber/I");
  TagSide->Branch("tlv_bTag","TLorentzVector",&tlv_bTag) ;
  TagSide->Branch("VtxCharge",&VtxCharge,"VtxCharge/I");
  TagSide->Branch("VtxMass",&VtxMass,"VtxMass/F");
  TagSide->Branch("tlv_vertex","TLorentzVector",&tlv_vertex) ;
  TagSide->Branch("tlv_mupTag","TLorentzVector",&tlv_mupTag) ;
  TagSide->Branch("tlv_mumTag","TLorentzVector",&tlv_mumTag) ;
  TagSide->Branch("tlv_kapTag","TLorentzVector",&tlv_kapTag) ;
  TagSide->Branch("tlv_kamTag","TLorentzVector",&tlv_kamTag) ;

  ProbeSide = new TTree("ProbeSide","Small Data Tree Probe Side") ;
  TagSide->Branch("EventNumber",&EventNumber,"EventNumber/I");
  ProbeSide->Branch("Rank",&Rank,"Rank/I") ;
  ProbeSide->Branch("bCode",&bCode,"bCode/I") ;
  ProbeSide->Branch("tlv_bDec","TLorentzVector",&tlv_bDec) ;
  ProbeSide->Branch("tlv_cDec","TLorentzVector",&tlv_cDec) ;
  ProbeSide->Branch("tlv_nuDec","TLorentzVector",&tlv_nuDec) ;
  ProbeSide->Branch("tlv_muDec","TLorentzVector",&tlv_muDec) ;
  ProbeSide->Branch("tlv_muPrb","TLorentzVector",&tlv_muPrb) ;
  ProbeSide->Branch("tlv_vDec","TLorentzVector",&tlv_vDec) ;
  fSmallNtuple->Print();

  return;

}


void PDAnalyzer::reset() {
// The macro "UTIL_USE" is automatically set in other source files,
// according to the environment where this class is being used.
#  if UTIL_USE == FULL
  // The whole ntuple content can be automatically reset at zero,
  // and std::vectors are cleared, by calling the "autoReset()" function.
  // This option is not available when not using the full utility.
  autoReset();
#elif UTIL_USE == BARE
  // If ntu content is to be reset or cleared, that should be done manually
  // when not using the full utility, i.e. when using this class as a 
  // simple ROOT macro.
  // This can be skipped, anyway, if there is not a specific reason to 
  // reset or clear all data before overwriting them with the ntuple content.
  nMuons = 0;
  muoPt ->clear();
  muoEta->clear();
  muoPhi->clear();
  // and so on...
#endif
  return;
}


bool PDAnalyzer::analyze( int entry, int event_file, int event_tot ) {

  bool flag(true) ;

  TimeMonitor( entry, event_file, event_tot );

  vector<int> *LLGenList = new vector<int> ; 
  if( nGenP > 0 ) GetLongLivedList( LLGenList) ;
  //  cout << " Long Lived " << LLGenList->size() << endl;
  
  // ============================================================
  // Get secondary Vertex Tracks
  tlv_mumTag->SetXYZT(0,0,0,0);
  tlv_mupTag->SetXYZT(0,0,0,0);
  tlv_kapTag->SetXYZT(0,0,0,0);
  tlv_kamTag->SetXYZT(0,0,0,0);

  bool foundSvt(false) ; 
  VtxCharge=0 ;
  
  for ( int iSV = 0; iSV < nSVertices; ++iSV ) 
    {
      if ( svtType->at( iSV ) < 3 ) continue;
      int vType = svtType->at( iSV ) ;
      
      if( vType == PDEnumString::svtBuJPsiK ||
	  vType == PDEnumString::svtBdJPsiKx ||
	  vType == PDEnumString::svtBsJPsiPhi )
	{
	  if( event_tot<100 ) cout << " **************** Secondary Vertex Found with: " ;
	  vector<int> trkFromSV =tracksFromSV( iSV ) ;
	  if( event_tot<100 ) cout << trkFromSV.size() << endl ;
	  TLorentzVector sPart(0,0,0,0) ;
	  for( uint j=0; j<trkFromSV.size() ; j++ ) 
	    {  
	      int itk = trkFromSV.at(j) ;
	      TLorentzVector aPart ;
	      bool isMuon = ( trkType->at(itk)>pow(2,10) );
	      double trkMass = (isMuon ? 0.105 : 0.494 ) ;
	      aPart.SetPtEtaPhiM(trkPt->at(itk),trkEta->at(itk),trkPhi->at(itk),trkMass) ;
	      if( isMuon && trkCharge->at(itk)>0 ) *tlv_mupTag = aPart ;
	      else if( isMuon && trkCharge->at(itk)<0 ) *tlv_mumTag = aPart ;
	      else if( !isMuon && trkCharge->at(itk)>0 ) *tlv_kapTag = aPart ;
	      else if( !isMuon && trkCharge->at(itk)<0 ) *tlv_kamTag = aPart ;
	      sPart += aPart ;
	      VtxCharge += trkCharge->at(itk) ;
	    }
	  for( int ig=0 ; ig<nGenP ; ig++ ) 
	    {
	      int LundCode = abs( genId->at(ig) ) ;
	      if( LundCode != LuBpl ) continue ;
	      double dR = sqrt( pow( genEta->at(ig)-sPart.Eta(),2) + pow( genPhi->at(ig)-sPart.Phi(),2 ) );
	      double dPt= 1-sPart.Pt()/genPt->at(ig) ;
	      dPtVsdR->Fill( dR, dPt ) ;
	      if( dPt>0.05 ) continue ;
	      if( dR>0.01 ) continue ;
	      tlv_bTag->SetPtEtaPhiM( genPt->at(ig),genEta->at(ig),genPhi->at(ig),genMass->at(ig) );
	    }
	  VtxMass = svtMass->at(iSV ) ;
	  if( VtxMass<5.5 ) foundSvt = true ;
	  tlv_vertex->SetXYZT( svtDirX->at(iSV)*svtDist3D->at(iSV),
			       svtDirY->at(iSV)*svtDist3D->at(iSV),
			       svtDirZ->at(iSV)*svtDist3D->at(iSV),
			       svtDist3D->at(iSV)/svtSigma3D->at(iSV) ) ;

	  if( event_tot<100 ) {
	    printf(" %6d %6d %7.3f %7.3f %7.3f %7.1f %10.3f %10.3f \n", 0 , VtxCharge , sPart.Px()/sPart.P(), sPart.Py()/sPart.P(), sPart.Pz()/sPart.P(), sPart.P(), sPart.M(), VtxMass ) ;
	    printf(" %6d %6d %7.3f %7.3f %7.3f %7.1f %10.3f \n", 1 , VtxCharge , tlv_vertex->Px()/tlv_vertex->P(), tlv_vertex->Py()/tlv_vertex->P(), tlv_vertex->Pz()/tlv_vertex->P(), tlv_vertex->P(), tlv_vertex->M()) ;
	  }
	  break ;
	}
    }
  //  if( !foundSvt ) cout << " ciccia " << endl ;
  if( foundSvt ) TagSide->Fill();      

  // ============================================================
  // Look for semi-muonic decay from probe side 

  tlv_bDec->SetXYZT(0,0,0,0);
  tlv_cDec->SetXYZT(0,0,0,0);
  tlv_nuDec->SetXYZT(0,0,0,0);
  tlv_muDec->SetXYZT(0,0,0,0);
  tlv_muPrb->SetXYZT(0,0,0,0);
  tlv_vDec->SetXYZT(0,0,0,0);

  bool FoundDecay( false ) ;
  std::vector<int> *DecayPos = new std::vector<int> ;
  std::vector<int> *DecayRank = new std::vector<int> ;

  int nInList = 0 ;
  if( FindDecayMode( nBpSml, ListBpDzMuNu, DecayPos, DecayRank ) )
    { nInList = nBpSml ; }
  else if( FindDecayMode( nBzSml, ListBzDpMuNu, DecayPos, DecayRank ) )
    { nInList = nBzSml ; }    
  else if( FindDecayMode( nBsSml, ListBsDsMuNu, DecayPos, DecayRank ) )
    { nInList = nBsSml ; }
    
  if( nInList>0 )
    {
      double prodX(0),prodY(0),prodZ(0);
      double decyX(0),decyY(0),decyZ(0);

      Rank=0 ;
      int iMuTag(-1);
      TLorentzVector sPart ;
      for( uint j=0; j<DecayPos->size() ; j++)
	{
	  int i = DecayPos->at(j) ;
	  TLorentzVector aPart;
	  aPart.SetPtEtaPhiM( genPt->at(i),genEta->at(i),genPhi->at(i),genMass->at(i));

	  // production point
	  if( j == 0 ){ prodX = genVx->at(i); prodY = genVy->at(i); prodZ = genVz->at(i); bCode = genId->at(i) ; }

	  if( j == 0 ) *tlv_bDec = aPart ;
	  else if( j == 1 ) {*tlv_cDec = aPart;}
	  else if( j == 2 ) {*tlv_nuDec = aPart; }
	  else if( j == 3 ) {*tlv_muDec = aPart; }

	  if( j>0 ) { sPart += aPart ; Rank+=DecayRank->at(j)*pow(10,j-1) ; }     
	  if( abs(genId->at(i)) != LuMuo ) continue;

	  for( int k=0 ; k< nMuons ; k++ ){
	    if( muoPt->at(k)<4 ) continue ;
	    if( genCharge->at(i) != muoCharge->at(k) ) continue ;
	    double deltaR = sqrt( pow(genEta->at(i) - muoEta->at(k),2)+pow(genPhi->at(i)-muoPhi->at(k),2)) ;
	    double deltPt = 1 - genPt->at(i)/muoPt->at(k) ;
	    // dPtVsdR->Fill( deltaR, deltPt ) ;
	    if( deltaR>0.01 ) continue ;
	    if( abs(deltPt)>0.1 ) continue ;

	    iMuTag = k ;
	    tlv_muPrb->SetPtEtaPhiM( muoPt->at(k), muoEta->at(k), muoPhi->at(k),0.105 ) ;
	    decyX = genVx->at(i); decyY = genVy->at(i); decyZ = genVz->at(i); 
	    tlv_vDec->SetXYZM( decyX-prodX, decyY-prodY, decyZ-prodZ, 0); 
	  }
	}

      if( iMuTag == -1 ) return false ;
      if( Rank > 119   ) return false ;
      
      nFound++ ;
      FoundDecay = true ;
      /*
      cout << " ++++ " << "\t" << " Found Decay " << nFound << endl ;
      printf(" %6d %6d %7.1f %7.1f %7.1f %7.1f %10.3f \n", 0 , Rank, sPart.Px(), sPart.Py(), sPart.Pz(), sPart.E(), sPart.M() ) ;
      printf(" %6d %6d %7.1f %7.1f %7.1f %7.1f %10.3f \n", 1 , Rank, tlv_bDec->Px(), tlv_bDec->Py(), tlv_bDec->Pz(), tlv_bDec->E(), tlv_bDec->M() ) ; 
      cout << endl ;
      */
    }
  if( FoundDecay ) ProbeSide->Fill();      

#if REDUCE_NTUPLE != 0
  // set reduced ntuple data
  rWriter->nSum = nMuons + nElectrons;
  rWriter->nPro = nMuons * nElectrons;
  rWriter->pTmu = ptmu;
  // fill reduced ntuple
  rWriter->fill();
#endif
  
  // ============================================================
  // Tag Side B meson, FS (to do list)
  
  
#if SKIM_NTUPLE != 0
  
  if ( flag ) fillSkim(); 
  
#endif
  
  delete LLGenList;
  return flag;
 }


void PDAnalyzer::endJob() {

  TagSide->Write();
  ProbeSide->Write();
  fSmallNtuple->Print();
  fSmallNtuple->Close();

#if SKIM_NTUPLE != 0
  closeSkim(); // close the skimmed ntuple file
#endif

#if REDUCE_NTUPLE != 0
  rWriter->close(); // close file for reduced ntuple
#endif

  // ============================================================
  // FS June 2022
  fSmallNtuple->Close();

  return;

}


// The following function is optional and it's aimed at saving histograms
// when data processing is finished.
// Actually it's needed only when not using the full utility, otherwise
// the function could simply be removed, relying on the default behaviour.
void PDAnalyzer::save() {
// The macro "UTIL_USE" is automatically set in other source files,
// according to the environment where this class is being used.
#  if UTIL_USE == FULL
  // All histos are automatically saved by calling the "autoSave()" function,
  // see the "book()" function for more informations.
  // This option is not available when not using the full utility, i.e. when
  // using this class as a simple ROOT macro;
  // on the contrary it's the default when the full utility i used, 
  // so in that case the whole function could be simply removed.
  autoSave();
#elif UTIL_USE == BARE
  // When not using the full utility, i.e. when using this class as a
  // simple ROOT macro, histograms are to be saved explicitly.
  hptmumax->Write();
  hptmu2nd->Write();
  hptmu   ->Write();
  hMass1  ->Write();
  hMass2  ->Write();
  hMass3  ->Write();
#endif

  return;
}


/*
// The following function is optional and it's aimed at making some plots
// when data processing is finished.
// If implemented, the Gpad library must be added to the
//   TMPAnalysis/Ntu/BuildFile.xml
// with the instruction
// <flags LDFLAGS="-lGpad"/>
// or
// <lib   name="Gpad"/>
// DO NOT leave here an empty function, or a function without any ROOT object
// drawing, otherwise the execution could get stuck in some situations.
void PDAnalyzer::plot() {
  TCanvas* can = new TCanvas( "muoPt", "muoPt", 800, 600 );
  can->cd();
  can->Divide( 1, 2 );
  can->cd( 1 );
  hptmumax->Draw();
  can->cd( 2 );
  hptmu2nd->Draw();
  return;
}
*/

