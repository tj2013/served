#ifndef SERVED_ASYNC_FILE_MANAGER_HPP
#define SERVED_ASYNC_FILE_MANAGER_HPP

#include <uv.h>
#include "asyncfile.hpp"

namespace served { namespace async {

    class AsyncFileManager {
    public:
        static AsyncFile * create();
    private:
        uv_loop_t m_loop;
    };
}}