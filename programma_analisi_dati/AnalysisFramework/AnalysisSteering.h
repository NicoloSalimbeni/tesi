#ifndef AnalysisSteering_h
#define AnalysisSteering_h

#include <set>

class AnalysisObject;
class Visitor;

class AnalysisSteering
{
public:
    static void AcceptAll(Visitor *v);

    static void subscribe(AnalysisObject *an);
    static void unsubscribe(AnalysisObject *an);

private:
    AnalysisSteering();
    ~AnalysisSteering();
    static std::set<AnalysisObject *> *aL();
};

#endif