#ifndef ObjColl_h
#define ObjColl_h
#include "../AnalysisFramework/AnalysisObject.h"
#include "../AnalysisFramework/Visitor.h"

class ObjColl : public AnalysisObject
{
public:
    ObjColl();
    ~ObjColl();
    void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis, const TLorentzVector &tlv_vertex) override;
    void Accept(Visitor *) override;
};

#endif