#ifndef AnalysisInfo_h
#define AnalysisInfo_h

#include <vector>
#include <string>

class AnalysisInfo
{
public:
    AnalysisInfo(std::string &);
    ~AnalysisInfo();

    void TakeArgoments(std::string &);
    bool Contains(std::string);

private:
    std::vector<std::string> argoments;
};

#endif