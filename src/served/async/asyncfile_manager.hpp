#ifndef SERVED_ASYNC_FILE_MANAGER_HPP
#define SERVED_ASYNC_FILE_MANAGER_HPP

#include <set>
#include <mutex>
#include <uv.h>
#include "asyncfile.hpp"

namespace served { namespace async {

class AsyncFileManager : {
private:
    std::set<std::shared_ptr<AsyncFile> > m_files;
    std::mutex               m_mutex;
    AsyncFileManager()
    {     
    }
public:
    AsyncFile & create(char * const);
    void AsyncFileManager::remove(std::shared_ptr<AsyncFile> & spFile);
    void init();
    ~AsyncFileManager();
    static AsyncFileManager * getInstance();
private:
    uv_loop_t m_loop;
    uv_timer_t m_timer;
};

}}