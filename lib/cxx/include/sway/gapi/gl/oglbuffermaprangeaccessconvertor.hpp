#ifndef SWAY_GAPI_GL_OGLBUFFERMAPRANGEACCESSCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBUFFERMAPRANGEACCESSCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/buffermaprangeaccesses.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLBufferMapRangeAccessConvertor final {
public:
  static auto toGLenum(BufferMapRangeAccess access) -> GLenum {
    switch (access) {
      case BufferMapRangeAccess::READ:
        return GL_MAP_READ_BIT;
      case BufferMapRangeAccess::WRITE:
        return GL_MAP_WRITE_BIT;
      case BufferMapRangeAccess::INVALIDATE_RANGE:
        return GL_MAP_INVALIDATE_RANGE_BIT;
      case BufferMapRangeAccess::INVALIDATE_BUFFER:
        return GL_MAP_INVALIDATE_BUFFER_BIT;
      case BufferMapRangeAccess::FLUSH_EXPLICIT:
        return GL_MAP_FLUSH_EXPLICIT_BIT;
      case BufferMapRangeAccess::UNSYNCHRONIZED:
        return GL_MAP_UNSYNCHRONIZED_BIT;
      default:
        return 0;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLBUFFERMAPRANGEACCESSCONVERTOR_HPP
