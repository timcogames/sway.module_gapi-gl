#ifndef SWAY_GAPI_GL_OGLBUFFERIDGENERATOR_HPP
#define SWAY_GAPI_GL_OGLBUFFERIDGENERATOR_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglgenericbufferhelper.hpp>
#include <sway/gapi/idgenerator.hpp>

#include <queue>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

#define BUFFER_IDS_CHUNK_CAPACITY 10

using BufferIdType = u32_t;
using BufferIdContainer = std::deque<BufferIdType>;

class OGLBufferIdGenerator : public std::queue<BufferIdType, BufferIdContainer>, public IdGenerator {
public:
  static auto createInstance() -> IdGeneratorPtr_t;

  OGLBufferIdGenerator();

  virtual ~OGLBufferIdGenerator();

  [[nodiscard]]
  auto newGuid() -> BufferIdType;

private:
  OGLGenericBufferHelper helper_;
  i32_t chunkCapacity_;
  std::vector<u32_t> used_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLBUFFERIDGENERATOR_HPP
