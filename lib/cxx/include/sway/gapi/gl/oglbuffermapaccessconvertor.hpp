#ifndef SWAY_GAPI_GL_OGLBUFFERMAPACCESSCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBUFFERMAPACCESSCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/buffermapaccesses.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLBufferMapAccessConvertor final {
public:
  static auto toGLenum(BufferMapAccess::Enum access) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
    switch (access) {
      case BufferMapAccess::Enum::READ:
        return GL_READ_ONLY;
      case BufferMapAccess::Enum::WRITE:
        return GL_WRITE_ONLY;
      case BufferMapAccess::Enum::READ_WRITE:
        return GL_READ_WRITE;
      default:
        return 0;
    }
#else
    switch (access) {
      case BufferMapAccess::Enum::READ:
        return GL_READ_ONLY_ARB;
      case BufferMapAccess::Enum::WRITE:
        return GL_WRITE_ONLY_ARB;
      case BufferMapAccess::Enum::READ_WRITE:
        return GL_READ_WRITE_ARB;
      default:
        return 0;
    }
#endif
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLBUFFERMAPACCESSCONVERTOR_HPP
