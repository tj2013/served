#ifndef SERVED_ASYNC_OBSERVER_HPP
#define SERVED_ASYNC_OBSERVER_HPP

namespace served { namespace async {

class Observer {
public:
    virtual void onData(char * const data, unsigned long len) = 0;
    virtual void onEnd() = 0; 
};

}}
