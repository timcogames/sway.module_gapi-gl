#ifndef SWAY_GAPI_GL_BUFFERIDGENERATOR_HPP
#define SWAY_GAPI_GL_BUFFERIDGENERATOR_HPP

#include <sway/gapi/gl/bufferhelper.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/idgenerator.hpp>

#include <queue>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

#define BUFFER_IDS_CHUNK_CAPACITY 10

using BufferIdType = u32_t;

template <typename T, typename Container = std::deque<T>>
class BufferIdGenerator : public std::queue<T, Container>, public IdGenerator {
public:
  static auto createInstance() -> std::shared_ptr<IdGenerator> { return std::make_shared<BufferIdGenerator>(); }

  BufferIdGenerator()
      : helper_(gapi::Extension::extensions)
      , chunkCapacity_(BUFFER_IDS_CHUNK_CAPACITY) {}

  virtual ~BufferIdGenerator() {
    helper_.DeleteBuffers(this->size(), std::vector<BufferIdType>({this->c.begin(), this->c.end()}).data());
  }

  [[nodiscard]] auto newGuid() -> BufferIdType {
    if (this->empty()) {
      auto *bufferIds = new BufferIdType[chunkCapacity_];
      helper_.GenerateBuffers(chunkCapacity_, bufferIds);

      for (u32_t i = 0; i < chunkCapacity_; i++) {
        this->push(bufferIds[i]);
      }

      SAFE_DELETE_ARRAY(bufferIds);
    }

    auto uniqueid = this->front();
    this->pop();

    return uniqueid;
  }

private:
  BufferHelper helper_;
  u32_t chunkCapacity_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_BUFFERIDGENERATOR_HPP
