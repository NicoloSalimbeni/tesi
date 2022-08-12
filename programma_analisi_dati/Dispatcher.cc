#include "Dispatcher.h"
#include <set>
#include "Observer.h"
#include "TLorentzVector.h"

class AnalysisObject;

std::set<Observer *> *Dispatcher::oL()
{
    static std::set<Observer *> *ptr = new std::set<Observer *>;
    return ptr;
}

void Dispatcher::subscribe(Observer *obs)
{
    oL()->insert(obs);
}

void Dispatcher::unsubscribe(Observer *obs)
{
    oL()->erase(obs);
}

void Dispatcher::Notify(const TLorentzVector &tlv_Btag, const TLorentzVector &tlv_visibile)
{
    std::set<Observer *>::iterator it = oL()->begin();
    std::set<Observer *>::iterator ei = oL()->end();
    while (it != ei)
    {
        (*it++)->Update(tlv_Btag, tlv_visibile);
    }
    return;
}
