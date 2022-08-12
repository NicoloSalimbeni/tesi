#ifndef Visitor_h
#define Visitor_h

class ObjColl;
class ObjImpColl;
class ObjNonColl;
class ObjAn;
class ObjAnColl;

class Visitor
{
    Visitor();
    ~Visitor();
    virtual void Visit(ObjColl *);
    virtual void Visit(ObjImpColl *);
    virtual void Visit(ObjNonColl *);
    virtual void Visit(ObjAn *);
    virtual void Visit(ObjAnColl *);
};

#endif