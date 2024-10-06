#ifndef SWAY_GAPI_GL_OGLBUFFERTARGETCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBUFFERTARGETCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/buffertargets.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLBufferTargetConvertor final {
public:
  static auto toGLenum(BufferTarget::Enum target) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
    switch (target) {
      case BufferTarget::Enum::ARRAY:
        return GL_ARRAY_BUFFER;
      case BufferTarget::Enum::ELEMENT_ARRAY:
        return GL_ELEMENT_ARRAY_BUFFER;
      default:
        return 0;
    }
#else
    switch (target) {
      case BufferTarget::Enum::ARRAY:
        return GL_ARRAY_BUFFER_ARB;
      case BufferTarget::Enum::ELEMENT_ARRAY:
        return GL_ELEMENT_ARRAY_BUFFER_ARB;
      default:
        return 0;
    }
#endif
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLBUFFERTARGETCONVERTOR_HPP
