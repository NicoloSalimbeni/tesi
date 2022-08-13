#include "AnalysisInfo.h"
#include <string>
#include <sstream>
AnalysisInfo::AnalysisInfo(std::string &s)
{
    TakeArgoments(s);
}

AnalysisInfo::~AnalysisInfo() {}

void AnalysisInfo::TakeArgoments(std::string &s)
{
    std::stringstream argoments_input(s);
    std::string temp;
    while (argoments_input >> temp)
    {
        argoments.push_back(temp);
    }
}

bool AnalysisInfo::Contains(std::string argomento_da_cercare)
{
    for (auto argomento_nesimo : argoments)
    {
        if (argomento_nesimo == argomento_da_cercare)
        {
            return true;
        }
    }
    return false;
}
