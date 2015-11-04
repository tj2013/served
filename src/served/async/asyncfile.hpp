#ifndef SERVED_ASYNC_FILE_HPP
#define SERVED_ASYNC_FILE_HPP

#include <string>
#include <uv.h>
#include "observable.hpp"

namespace served { namespace async {

    class AsyncFile;

    struct PipeWrapper {
        uv_pipe_t m_pipe;
        AsyncFile * m_pAsyncFile;
    };

    class AsyncFile: public Observable {
    public:
        virtual subscribe(Observer & _observer) {
            m_Observer = _observer;
        }
        AsyncFile(char * const filename, uv_loop_t loop):
            m_filename(filename),
            m_loop(loop),
            pObserver(nullptr)
        {

        }
        void startRead();
    private:
        Observer * pObserver;
        uv_loop_t & m_loop;
        int m_file_discriptor;
        uv_fs_t m_file_request;
        std::string m_filename;
        PipeWrapper m_file_pipe_wrapper;
    };

    
}}