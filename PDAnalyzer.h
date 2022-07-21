#ifndef PDAnalysis_Ntu_PDAnalyzer_h
#define PDAnalysis_Ntu_PDAnalyzer_h

#include "TH1.h"
#include "TH2.h"
#include "PDAnalyzerUtil.h"
#include "PDAnalysis/Ntu/interface/PDGenHandler.h"

// ==========================================================
//   F.S. June 2022

#include "TStopwatch.h"
#include <iostream>
#include <sstream>
using namespace std;

// end FS
// ==========================================================


// additional features
//#include "DataSetFilter.h"                       // dataset filter

// Activate/deactivate lines to skim ntuple:
// a macro is used just to flag the relevant code lines, 
// normally the code would not make use of the preprocessor.

// Do not do the ntuple skim
#define SKIM_NTUPLE 0
// Do the ntuple skim
//#define SKIM_NTUPLE 1

#if SKIM_NTUPLE != 0
#include "NtuTool/Common/interface/TreeFilter.h"
#include "TFile.h"
#endif

// Activate/deactivate lines to produce a reduced ntuple:
// a macro is used just to flag the relevant code lines, 
// normally the code would not make use of the preprocessor.

// Do not produce a reduced ntuple
#define REDUCE_NTUPLE 0
// Produce a reduced ntuple
//#define REDUCE_NTUPLE 1

#if REDUCE_NTUPLE != 0
class PDReducedNtupleWriter;
#endif

class PDAnalyzer: public virtual PDAnalyzerUtil
,                 public virtual PDGenHandler
#if SKIM_NTUPLE != 0
                 , public virtual TreeFilter // additional header file
                                             // to skim ntuples
#endif
// additional features
//               , public virtual DataSetFilter // dataset filter
 {

 public:

  PDAnalyzer();
  virtual ~PDAnalyzer() override;

  // function called before starting the analysis
  void beginJob() override;

  // functions to book the histograms
  void book() override;

  // functions called for each event
  // function to reset class content before reading from file
  void reset() override;
  // function to do event-by-event analysis,
  // return value "true" for accepted events
  bool analyze( int entry, int event_file, int event_tot ) override;

  // function called at the end of the analysis
  void endJob() override;

  // functions called at the end of the event loop
  using WrapperBase::plot; // needed for the following declaration
//  void plot() override; // plot histograms on the screen (optional, see .cc)
  using WrapperBase::save;
  void save() override; // save histograms on a ROOT file (optional, see .cc)

  bool verbose;

    
 protected:

  double ptCut;

#if REDUCE_NTUPLE != 0
  PDReducedNtupleWriter* rWriter;
#endif
  // ==============================================================================================================
  // FS June 2022

  // ************************************************************
  bool FindDecayMode( const int nPart, int *DecayMode, vector<int> *GenList, vector<int> *Rank )
  {
    bool gotcha(false);
    if( nGenP== 0 ) return gotcha ;
    if( nPart == 0 ) return gotcha ;
    
    int LundIdMother = DecayMode[0] ;
    vector <int> MotherList; 
    
    for( int i=0; i<nGenP ; i++) { if( abs(genId->at(i)) == LundIdMother ) MotherList.push_back(i) ; }
    for( uint i=0; i<MotherList.size(); i++ ) if( GetDecayList( i, MotherList.at(i), nPart, DecayMode, GenList, Rank) ) gotcha = true ;
    return gotcha;
  }
 // ************************************************************
  inline bool GetDecayList( uint iPos, int iMother, const int nPart, int *DecayMode, vector<int> *GenList, vector<int>* Rank )
  {
    int already_used[nGenP]={nGenP*0};
    vector<int> *ThisGenList = new vector<int> ;
    vector<int> *ThisRank = new vector<int>;
    
    int MotherSign = ( genId->at(iMother)>0 ? 1 : -1 ) ;
    ThisGenList->push_back(iMother);
    ThisRank->push_back(0);

    for( int j=1 ; j<nPart ; j++ )
      { 
	bool gotThis(false);
	int LundCode = DecayMode[j]*MotherSign ;
	for( int i=0; i<nGenP ; i++ )
	  {
	    if( genId->at(i) != LundCode || already_used[i] == 1 ) continue ;
	    int itsMother = genMother->at(i) ;
	    int rank=1;
	    while( itsMother>= 0 )  {
	      if( itsMother == iMother ) {
		gotThis = true;
		itsMother=-1 ;
		ThisRank->push_back(rank);
		ThisGenList->push_back(i) ;
		already_used[i]=1;
	      }
	      else {
		itsMother = genMother->at(itsMother) ;
		rank++;
	      }
	    }
	    if( gotThis ) break ;
	  }
	if( !gotThis ) break;
      }
    
    if( (int) ThisGenList->size() != nPart ) 
      {
	delete ThisGenList ;
	delete ThisRank;
	return false ;
      }
    for( uint i=0 ; i<ThisGenList->size(); i++ )
      {
	GenList->push_back( ThisGenList->at(i)) ;
	Rank->push_back(ThisRank->at(i)) ;
      }
    delete ThisGenList;
    delete ThisRank;
    return true ;
  }
  // ************************************************************
  void TimeMonitor( int entry, int event_file, int event_tot )
  {
    
    if( entry==0 )
      {
        timer = new TStopwatch();
	timer->Start();
	t_cpu = t_real = 0 ;
	cout << " ==================================== " << endl ;
	cout << " Start of time monitor " << endl ;
	cout << " ==================================== " << endl ;
      }

    if( entry == 10 || entry == 100 || entry==1000 || entry%10000==0 )
      {
	t_real +=timer->RealTime() ;
	t_cpu  +=timer->CpuTime() ;
	
	printf(" At event %9d", event_tot );
	printf(" Event file %9d", event_file );
	printf(" Cpu Time(s) %9.2f", t_cpu);
	printf(" Real Time(s) %9.2f ", t_real ) ;
	printf("\n");

	timer->Start() ;
      } 
  }
  // ************************************************************
  void GetLongLivedList( vector<int> *LLGenList )
  {
    LLGenList->clear() ;
    for( int i=0; i<nGenP; i++)
      {
	int aLund =abs(genId->at(i)) ;
	if( aLund == 11 || aLund == 13 || aLund == 211 || aLund == 321 || aLund == 2212 ) LLGenList->push_back(i) ;
      }
  }
// 
 private:

  TH1D* hptmumax;
  TH1D* hptmu2nd;
  TH1D* hptmu;

  TH1F* hMass1;
  TH1F* hMass2;
  TH1F* hMass3;

  TH2D* dPtVsdR ;
  // dummy copy constructor and assignment
  PDAnalyzer           ( const PDAnalyzer& ) = delete;
  PDAnalyzer& operator=( const PDAnalyzer& ) = delete;

  // ==============================================
  // FS June 2022
  TStopwatch *timer ;
  double t_cpu, t_real; 
  int nFound ;
 };


#endif // PDAnalysis_Ntu_PDAnalyzer_h

