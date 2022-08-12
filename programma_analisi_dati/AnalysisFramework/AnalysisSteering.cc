#include "AnalysisSteering.h"
#include "AnalysisObject.h"
#include "Visitor.h"
#include <set>

AnalysisSteering::AnalysisSteering() {}

AnalysisSteering::~AnalysisSteering() {}

std::set<AnalysisObject *> *AnalysisSteering::aL()
{
    static std::set<AnalysisObject *> *ptr = new std::set<AnalysisObject *>;
    return ptr;
}

void AnalysisSteering::subscribe(AnalysisObject *obs)
{
    aL()->insert(obs);
}

void AnalysisSteering::unsubscribe(AnalysisObject *obs)
{
    aL()->erase(obs);
}

void AnalysisSteering::AcceptAll(Visitor *v)
{
    std::set<AnalysisObject *>::iterator it = aL()->begin();
    std::set<AnalysisObject *>::iterator ei = aL()->end();
    while (it != ei)
    {
        (*it++)->Accept(v);
    }
    return;
}