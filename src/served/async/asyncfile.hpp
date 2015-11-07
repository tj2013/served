#ifndef SERVED_ASYNC_FILE_HPP
#define SERVED_ASYNC_FILE_HPP

#include <memory>
#include <string>
#include <uv.h>

namespace served { namespace async {

class AsyncFile;
class AsyncFileManager;

struct PipeWrapper {
    uv_pipe_t m_pipe;
    AsyncFile * m_pAsyncFile;
};

class AsyncFile: public std::enable_shared_from_this<AsyncFile>  {
public:

    AsyncFile(const AsyncFile&) = delete;

    AsyncFile& operator=(const AsyncFile&) = delete;

    explicit AsyncFile(char const *  filename, uv_loop_t & loop, AsyncFileManager & manager):
        m_filename(filename),
        m_loop(loop),
        m_manager(manager)
    {

    }
    
    void startRead(
            const std::function<void(char * const data, unsigned long len)> onData,
            const std::function<void()> & _onComplete);

    void close();
    
private:

    uv_loop_t & m_loop;
    int m_file_discriptor;
    uv_fs_t m_file_open_request;
    std::string m_filename;
    PipeWrapper m_file_pipe_wrapper;
    AsyncFileManager & m_manager;
    static void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
    static void read_callback(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf);
    std::function<void(char * const data, unsigned long len)> onData;
    std::function<void()> onComplete;
};

}}

#endif