#ifndef SWAY_GAPI_GL_OGLBUFFERMAPACCESSCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBUFFERMAPACCESSCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/buffermapaccesses.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLBufferMapAccessConvertor final {
public:
  static auto toGLenum(BufferMapAccess access) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
    switch (access) {
      case BufferMapAccess::READ:
        return GL_READ_ONLY;
      case BufferMapAccess::WRITE:
        return GL_WRITE_ONLY;
      case BufferMapAccess::READ_WRITE:
        return GL_READ_WRITE;
      default:
        return 0;
    }
#else
    switch (access) {
      case BufferMapAccess::READ:
        return GL_READ_ONLY_ARB;
      case BufferMapAccess::WRITE:
        return GL_WRITE_ONLY_ARB;
      case BufferMapAccess::READ_WRITE:
        return GL_READ_WRITE_ARB;
      default:
        return 0;
    }
#endif
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLBUFFERMAPACCESSCONVERTOR_HPP
