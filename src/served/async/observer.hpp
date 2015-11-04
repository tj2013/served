#ifndef SERVED_ASYNC_OBSERVER_HPP
#define SERVED_ASYNC_OBSERVER_HPP

namespace served { namespace net {

class Observer {
public:
    virtual onData(char * const data, unsigned long len) = 0;
    virtual onEnd() = 0; 
};

}}
