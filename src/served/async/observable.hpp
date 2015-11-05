#ifndef SERVED_ASYNC_OBSERVABLE_HPP
#define SERVED_ASYNC_OBSERVABLE_HPP

#include "observer.h"

namespace served { namespace async {

class Observable {
public:
    virtual void subscribe(Observer * pObserver) = 0;
};

}}
