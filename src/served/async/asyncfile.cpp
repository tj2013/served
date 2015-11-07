#include <uv.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "asyncfile.hpp"
#include "asyncfile_manager.hpp"

using namespace served::async;

void AsyncFile::startRead(
        const std::function<void(char * const data, unsigned long len)> _onData,
        const std::function<void()> & _onComplete) {
    this->onData = _onData;
    this->onComplete = _onComplete;
    m_file_discriptor = uv_fs_open(&m_loop, &m_file_open_request, m_filename.c_str(), O_RDONLY, 0, NULL);
    //callback == NULL, synchrounous, return req->result, the file handle
    uv_pipe_init(&m_loop, &(m_file_pipe_wrapper.m_pipe), 0);
    uv_pipe_open(&(m_file_pipe_wrapper.m_pipe), m_file_discriptor);
    m_file_pipe_wrapper.m_pAsyncFile = this;
    uv_read_start((uv_stream_t*) &(m_file_pipe_wrapper.m_pipe), AsyncFile::alloc_buffer, AsyncFile::read_callback);
}

void AsyncFile::close() {
    auto self(shared_from_this());

    uv_close((uv_handle_t *)&(m_file_pipe_wrapper.m_pipe), NULL);
    //uv_fs_close is not needed, close pipe also close the file
    //uv_fs_req_cleanup not needed in sync call
    onComplete();
    m_manager.remove(shared_from_this());
}

//static
void AsyncFile::alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    *buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

//static
void AsyncFile::read_callback(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
    size_t off = offsetof(PipeWrapper, m_pAsyncFile)  - offsetof(PipeWrapper, m_pipe);
    char * p = (char*)stream;
    AsyncFile * pAsyncFile = (AsyncFile *) (p + off);
    if (nread < 0){
        if (nread == UV_EOF){
            pAsyncFile ->close();
        }
    } else if (nread > 0) {
        pAsyncFile->onData(buf->base, nread);
    }

    if (buf->base)
        free(buf->base);
}