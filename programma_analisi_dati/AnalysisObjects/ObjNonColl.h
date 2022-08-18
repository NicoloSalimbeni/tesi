#ifndef ObjNonColl_h
#define ObjNonColl_h
#include "../AnalysisFramework/AnalysisObject.h"
#include "../AnalysisFramework/Visitor.h"

class ObjNonColl : public AnalysisObject
{
public:
    ObjNonColl();
    ~ObjNonColl();
    void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis, const TLorentzVector &tlv_vertex) override;
    void Accept(Visitor *) override;

private:
    Double_t pvz;
};

#endif