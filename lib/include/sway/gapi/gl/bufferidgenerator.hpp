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
using BufferIdContainer = std::deque<BufferIdType>;

class BufferIdGenerator : public std::queue<BufferIdType, BufferIdContainer>, public IdGenerator {
public:
  static auto createInstance() -> std::shared_ptr<IdGenerator>;

  BufferIdGenerator();

  virtual ~BufferIdGenerator();

  [[nodiscard]] auto newGuid() -> BufferIdType;

private:
  BufferHelper helper_;
  s32_t chunkCapacity_;
  std::vector<u32_t> used_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_BUFFERIDGENERATOR_HPP
