#include "asyncfile_manager.hpp"

using namespace served::async;

AsyncFile * AsyncFileManager::create(char * const filename)
{
    return new AsyncFile(filename, m_loop);
}