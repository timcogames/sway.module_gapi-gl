#ifndef SWAY_GAPI_GL_OGLCLEARFLAGCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLCLEARFLAGCONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLClearFlagConvertor final {
public:
  static auto toGLbitfield(ClearFlag flags) -> GLbitfield {
    u32_t result = 0;

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

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLCLEARFLAGCONVERTOR_HPP
