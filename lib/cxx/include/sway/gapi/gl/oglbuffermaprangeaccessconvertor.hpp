#ifndef SWAY_GAPI_GL_OGLBUFFERMAPRANGEACCESSCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBUFFERMAPRANGEACCESSCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/buffermaprangeaccesses.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLBufferMapRangeAccessConvertor final {
public:
  static auto toGLenum(BufferMapRangeAccess::Enum access) -> GLenum {
    switch (access) {
      case BufferMapRangeAccess::Enum::READ:
        return GL_MAP_READ_BIT;
      case BufferMapRangeAccess::Enum::WRITE:
        return GL_MAP_WRITE_BIT;
      case BufferMapRangeAccess::Enum::INVALIDATE_RANGE:
        return GL_MAP_INVALIDATE_RANGE_BIT;
      case BufferMapRangeAccess::Enum::INVALIDATE_BUFFER:
        return GL_MAP_INVALIDATE_BUFFER_BIT;
      case BufferMapRangeAccess::Enum::FLUSH_EXPLICIT:
        return GL_MAP_FLUSH_EXPLICIT_BIT;
      case BufferMapRangeAccess::Enum::UNSYNCHRONIZED:
        return GL_MAP_UNSYNCHRONIZED_BIT;
      default:
        return 0;
    }
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLBUFFERMAPRANGEACCESSCONVERTOR_HPP
