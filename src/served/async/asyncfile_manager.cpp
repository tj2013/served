#include "asyncfile_manager.hpp"

using namespace served::async;

AsyncFile & AsyncFileManager::create(char * const filename)
{
    std::shared_ptr<AsyncFile> spFile = std::make_shared<AsyncFile>(filename, m_loop);
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_files.insert(c);
    }
    return *spFile;
}

void AsyncFileManager::remove(std::shared_ptr<AsyncFile> spFile)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_files.erase(spFile);
}

void timer_cb(uv_timer_t* handle)
{
    //do nothing
}

void AsyncFileManager::init()
{
    uv_loop_init(&m_loop);

    uv_timer_init(&m_loop, &m_timer);
    uv_timer_start(&m_timer, timer_cb, UINT64_MAX, 1);

    uv_run(&m_loop, UV_RUN_DEFAULT);
}

~AsyncFileManager::AsyncFileManager()
{
    uv_timer_stop(&m_timer);
    uv_loop_close(&m_loop);
}


