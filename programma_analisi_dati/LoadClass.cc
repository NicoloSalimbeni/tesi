void LoadClass()
{
    gROOT->ProcessLine(".L Utilities.cc");
    gROOT->ProcessLine(".L UtilitiesAnalysis.cc");
    gROOT->ProcessLine(".L Observer.cc");
    gROOT->ProcessLine(".L Dispatcher.cc");
    gROOT->ProcessLine(".L AnalysisObject.cc");
    gROOT->ProcessLine(".L ObjAn.cc");
    gROOT->ProcessLine(".L ObjAnColl.cc");
    gROOT->ProcessLine(".L ObjColl.cc");
    gROOT->ProcessLine(".L ObjImpColl.cc");
    gROOT->ProcessLine(".L ObjNonColl.cc");
    gROOT->ProcessLine(".L TagSide.cc");
}