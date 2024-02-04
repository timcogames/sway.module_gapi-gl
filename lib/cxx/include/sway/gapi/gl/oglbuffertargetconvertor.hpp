#ifndef SWAY_GAPI_GL_OGLBUFFERTARGETCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBUFFERTARGETCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/buffertargets.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLBufferTargetConvertor final {
public:
  static auto toGLenum(BufferTarget target) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
    switch (target) {
      case BufferTarget::ARRAY:
        return GL_ARRAY_BUFFER;
      case BufferTarget::ELEMENT_ARRAY:
        return GL_ELEMENT_ARRAY_BUFFER;
      default:
        return 0;
    }
#else
    switch (target) {
      case BufferTarget::ARRAY:
        return GL_ARRAY_BUFFER_ARB;
      case BufferTarget::ELEMENT_ARRAY:
        return GL_ELEMENT_ARRAY_BUFFER_ARB;
      default:
        return 0;
    }
#endif
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLBUFFERTARGETCONVERTOR_HPP
