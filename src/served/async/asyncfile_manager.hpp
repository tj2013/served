#ifndef SERVED_ASYNC_FILE_MANAGER_HPP
#define SERVED_ASYNC_FILE_MANAGER_HPP

#include <set>
#include <mutex>
#include <uv.h>
#include "asyncfile.hpp"

namespace served { namespace async {

class AsyncFileManager {
private:
    std::set<std::shared_ptr<AsyncFile> > m_files;
    std::mutex               m_mutex;
    
public:
    AsyncFileManager(const AsyncFileManager&) = delete;

    AsyncFileManager& operator=(const AsyncFileManager&) = delete;

    AsyncFileManager()
    {     
    }
    AsyncFile & create(char const *);
    void remove(std::shared_ptr<AsyncFile> spFile);
    void init();
    ~AsyncFileManager();
private:
    uv_loop_t m_loop;
    uv_timer_t m_timer;
};

}}

#endif