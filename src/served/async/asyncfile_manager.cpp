#include "asyncfile_manager.hpp"

using namespace served::async;

AsyncFile & AsyncFileManager::create(char const * filename)
{
    std::shared_ptr<AsyncFile> spFile = std::make_shared<AsyncFile>(filename, m_loop, *this);
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_files.insert(spFile);
    }
    return *spFile;
}

void AsyncFileManager::remove(std::shared_ptr<AsyncFile> const & spFile)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_files.erase(spFile);
}

static int counter = 0;
static void wait_for_a_while(uv_idle_t* handle) {
    counter++;
    if (counter % (1000*1000) == 0)
    {
        printf("idle counter = %d", counter);
    }
}  

void AsyncFileManager::init()
{
    uv_loop_init(&m_loop);

    uv_idle_init(&m_loop, &m_idler);
    uv_idle_start(&m_idler, wait_for_a_while);
    uv_run(&m_loop, UV_RUN_DEFAULT);
}

AsyncFileManager::~AsyncFileManager()
{
    uv_loop_close(&m_loop);
}


