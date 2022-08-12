#ifndef ObjColl_h
#define ObjColl_h
#include "../AnalysisFramework/AnalysisObject.h"

class ObjColl : public AnalysisObject
{
public:
    ObjColl();
    ~ObjColl();
    void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) override;
};

#endif