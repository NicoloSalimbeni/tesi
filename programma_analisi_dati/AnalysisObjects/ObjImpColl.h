#ifndef ObjImpColl_h
#define ObjImpColl_h
#include "../AnalysisFramework/AnalysisObject.h"

class ObjImpColl : public AnalysisObject
{
public:
    ObjImpColl();
    ~ObjImpColl();
    void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) override;
};

#endif