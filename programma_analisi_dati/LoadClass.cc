void LoadClass()
{
    gROOT->ProcessLine(".L ./AnalysisUtilities/Utilities.cc");
    gROOT->ProcessLine(".L ./AnalysisUtilities/UtilitiesAnalysis.cc");
    gROOT->ProcessLine(".L ./AnalysisFramework/Observer.cc");
    gROOT->ProcessLine(".L ./AnalysisFramework/Dispatcher.cc");
    gROOT->ProcessLine(".L ./AnalysisFramework/AnalysisObject.cc");
    gROOT->ProcessLine(".L ./AnalysisObjects/ObjAn.cc");
    gROOT->ProcessLine(".L ./AnalysisObjects/ObjAnColl.cc");
    gROOT->ProcessLine(".L ./AnalysisObjects/ObjColl.cc");
    gROOT->ProcessLine(".L ./AnalysisObjects/ObjImpColl.cc");
    gROOT->ProcessLine(".L ./AnalysisObjects/ObjNonColl.cc");
    gROOT->ProcessLine(".L TagSide.cc");
}