#ifndef ObjNonColl_h
#define ObjNonColl_h
#include "AnalysisObject.h"

class ObjNonColl : public AnalysisObject
{
public:
    ObjNonColl();
    ~ObjNonColl();
    void AddPoint(const TLorentzVector &tlv_B, const TLorentzVector &tlv_vis) override;

private:
    Double_t pvz;
};

#endif