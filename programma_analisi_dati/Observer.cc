#include "Observer.h"
#include "Dispatcher.h"
Observer::Observer()
{
    Dispatcher::subscribe(this);
}

Observer::~Observer()
{
    Dispatcher::unsubscribe(this);
}