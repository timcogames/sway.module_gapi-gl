#ifndef SWAY_GAPI_GL_OGLCLEARFLAGCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLCLEARFLAGCONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLClearFlagConvertor final {
public:
  static auto toGLbitfield(ClearFlag flags) -> GLbitfield {
    u8_t result = 0;

    if ((flags & ClearFlag::COLOR) == ClearFlag::COLOR) {
      result |= GL_COLOR_BUFFER_BIT;
    }

    if ((flags & ClearFlag::DEPTH) == ClearFlag::DEPTH) {
      result |= GL_DEPTH_BUFFER_BIT;
    }

    if ((flags & ClearFlag::STENCIL) == ClearFlag::STENCIL) {
      result |= GL_STENCIL_BUFFER_BIT;
    }

    return result;
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLCLEARFLAGCONVERTOR_HPP
