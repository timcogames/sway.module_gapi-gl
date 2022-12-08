#ifndef SWAY_GAPI_GL_BUFFERIDQUEUEIMPL_HPP
#define SWAY_GAPI_GL_BUFFERIDQUEUEIMPL_HPP

#include <sway/gapi/bufferIdqueue.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/prereqs.hpp>

#include <GLES2/gl2.h>
#include <queue>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

#define BUFFER_IDS_CHUNK_CAPACITY 10

using BufferIdType = u32_t;

template <typename T, typename Container = std::deque<T>>
class IterableQueue : public std::queue<T, Container> {
public:
  typedef typename Container::const_iterator const_iterator;

  const_iterator begin() const { return this->c.begin(); }
  const_iterator end() const { return this->c.end(); }
};

class BufferIdQueueImpl : public BufferIdQueue {
public:
  static auto createInstance() -> std::shared_ptr<BufferIdQueue> { return std::make_shared<BufferIdQueueImpl>(); }

  BufferIdQueueImpl()
      : chunkCapacity_(BUFFER_IDS_CHUNK_CAPACITY) {}

  ~BufferIdQueueImpl() {
#ifdef _EMSCRIPTEN
    glDeleteBuffers(queue_.size(), std::vector<BufferIdType>({queue_.begin(), queue_.end()}).data());
#else
    Extension::glDeleteBuffers(queue_.size(), std::vector<BufferIdType>({queue_.begin(), queue_.end()}).data());
#endif
  }

  [[nodiscard]] auto getBufferId() -> BufferIdType {
    if (queue_.empty()) {
      auto *bufferIds = new BufferIdType[chunkCapacity_];

#ifdef _EMSCRIPTEN
      glGenBuffers(chunkCapacity_, bufferIds);
#else
      Extension::glGenBuffers(chunkCapacity_, bufferIds);
#endif

      for (int i = 0; i < chunkCapacity_; i++) {
        queue_.push(bufferIds[i]);
      }

      SAFE_DELETE_ARRAY(bufferIds);
    }

    int uniqueid = queue_.front();
    queue_.pop();

    return uniqueid;
  }

private:
  IterableQueue<BufferIdType> queue_;
  u32_t chunkCapacity_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_BUFFERIDQUEUEIMPL_HPP
