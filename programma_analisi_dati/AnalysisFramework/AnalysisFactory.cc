#include "AnalysisFactory.h"
#include "AnalysisObject.h"
#include "AnalysisInfo.h"
#include <map>

AnalysisFactory::AnalysisFactory()
{
}

AnalysisFactory::~AnalysisFactory()
{
}

std::map<std::string, AnalysisObject *> *AnalysisFactory::GetAList()
{
    static std::map<std::string, AnalysisObject *> *ptr = new std::map<std::string, AnalysisObject *>;
    return ptr;
}

// create all requested analysis objects
std::map<std::string, AnalysisObject *> AnalysisFactory::create(AnalysisInfo *info)
{
    std::map<std::string, AnalysisObject *> *aList = GetAList();
    // loop over analysis object factories
    static std::map<std::string, AbsFactory *> *fm = factoryMap();
    for (const auto &element : *fm)
    {
        if (info->Contains(element.first) || info->Contains("all"))
        {
            aList->insert(std::make_pair(element.first, element.second->create()));
        }
    }
    return *aList;
}

// function to add analyzer concrete factories
void AnalysisFactory::registerFactory(const std::string &name, AbsFactory *b)
{
    static std::map<std::string, AbsFactory *> &fm = *factoryMap();
    fm[name] = b;
    return;
}

// map to associate analyzer names with corresponding factories
std::map<std::string, AnalysisFactory::AbsFactory *> *
AnalysisFactory::factoryMap()
{
    static std::map<std::string, AbsFactory *> *fm = new std::map<std::string, AbsFactory *>;
    return fm;
}

AnalysisObject *AnalysisFactory::GetObject(std::string oggetto)
{
    std::map<std::string, AnalysisObject *> *aList = GetAList();

    std::map<std::string, AnalysisObject *>::iterator it = aList->find(oggetto);
    std::map<std::string, AnalysisObject *>::iterator ie = aList->end();

    if (it != ie)
    {
        return it->second;
    }
    return nullptr;
}