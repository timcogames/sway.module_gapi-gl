#ifndef SWAY_GAPI_GL_BUFFERIDQUEUEIMPL_HPP
#define SWAY_GAPI_GL_BUFFERIDQUEUEIMPL_HPP

#include <sway/gapi/bufferidqueue.hpp>
#include <sway/gapi/gl/bufferhelper.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/prereqs.hpp>

#include <queue>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

#define BUFFER_IDS_CHUNK_CAPACITY 10

using BufferIdType = u32_t;

template <typename T, typename Container = std::deque<T>>
class IterableQueue : public std::queue<T, Container> {
public:
  using const_iterator = typename Container::const_iterator;

  const_iterator begin() const { return this->c.begin(); }
  const_iterator end() const { return this->c.end(); }
};

class BufferIdQueueImpl : public BufferIdQueue {
public:
  static auto createInstance() -> std::shared_ptr<BufferIdQueue> { return std::make_shared<BufferIdQueueImpl>(); }

  BufferIdQueueImpl()
      : helper_(gapi::Extension::extensions)
      , chunkCapacity_(BUFFER_IDS_CHUNK_CAPACITY) {}

  virtual ~BufferIdQueueImpl() {
    helper_.DeleteBuffers(queue_.size(), std::vector<BufferIdType>({queue_.begin(), queue_.end()}).data());
  }

  [[nodiscard]] auto newGuid() -> BufferIdType {
    if (queue_.empty()) {
      auto *bufferIds = new BufferIdType[chunkCapacity_];
      helper_.GenerateBuffers(chunkCapacity_, bufferIds);

      for (u32_t i = 0; i < chunkCapacity_; i++) {
        queue_.push(bufferIds[i]);
      }

      SAFE_DELETE_ARRAY(bufferIds);
    }

    auto uniqueid = queue_.front();
    queue_.pop();

    return uniqueid;
  }

private:
  BufferHelper helper_;
  IterableQueue<BufferIdType> queue_;
  u32_t chunkCapacity_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_BUFFERIDQUEUEIMPL_HPP
