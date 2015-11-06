#ifndef SERVED_ASYNC_FILE_HPP
#define SERVED_ASYNC_FILE_HPP

#include <memory>
#include <string>
#include <uv.h>
#include "observable.hpp"

namespace served { namespace async {

    class AsyncFile;

    struct PipeWrapper {
        uv_pipe_t m_pipe;
        AsyncFile * m_pAsyncFile;
    };

    class AsyncFile: public Observable, public std::enable_shared_from_this<AsyncFile>  {
    public:
        virtual addObserver(Observer * _pObserver) {
            m_pObserver = _pObserver;
        }
        AsyncFile(char * const filename, uv_loop_t & loop, AsyncFileManager & manager):
            m_filename(filename),
            m_loop(loop),
            m_pObserver(nullptr),
            m_manager(manager)
        {

        }
        
        void startRead();

        void close();
        
    private:
        Observer * m_pObserver;
        uv_loop_t & m_loop;
        int m_file_discriptor;
        uv_fs_t m_file_open_request;
        std::string m_filename;
        PipeWrapper m_file_pipe_wrapper;
        AsyncFileManager & m_manager;
    };

    
}}