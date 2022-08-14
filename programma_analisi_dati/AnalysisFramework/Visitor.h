#ifndef Visitor_h
#define Visitor_h

class ObjColl;
class ObjImpColl;
class ObjNonColl;
class ObjAnEs;
class ObjAnColl;

class Visitor
{
public:
    Visitor();
    virtual ~Visitor();
    virtual void Visit(ObjColl *) = 0;
    virtual void Visit(ObjImpColl *) = 0;
    virtual void Visit(ObjNonColl *) = 0;
    virtual void Visit(ObjAnEs *) = 0;
    virtual void Visit(ObjAnColl *) = 0;
};

#endif