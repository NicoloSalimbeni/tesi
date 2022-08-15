#include "../AnalysisObjects/ObjColl.h"
#include "../AnalysisObjects/ObjImpColl.h"
#include "../AnalysisObjects/ObjNonColl.h"
#include "../AnalysisObjects/ObjAnEs.h"
#include "../AnalysisObjects/ObjAnColl.h"
#include "ViStats.h"

#include <iostream>

ViStats::ViStats()
{
}

ViStats::~ViStats()
{
}

void ViStats::Visit(ObjColl *obj)
{
}

void ViStats::Visit(ObjImpColl *obj)
{
}

void ViStats::Visit(ObjNonColl *obj)
{
}

void ViStats::Visit(ObjAnEs *obj)
{
    obj->PrintFinalStats();
}

void ViStats::Visit(ObjAnColl *obj)
{
    obj->PrintFinalStats();
}
