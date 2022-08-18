#ifndef Dispatcher_h
#define Dispatcher_h

#include "TLorentzVector.h"

#include <set>

class Observer;

class Dispatcher
{
    friend class Observer;

public:
    static void Notify(const TLorentzVector &tlv_Btag, const TLorentzVector &tlv_visibile, const TLorentzVector &tlv_vertex);
    static void UnsubscribeAll();

private:
    Dispatcher(){};
    ~Dispatcher(){};
    static std::set<Observer *> *oL();
    static void subscribe(Observer *x);
    static void unsubscribe(Observer *x);
};

#endif