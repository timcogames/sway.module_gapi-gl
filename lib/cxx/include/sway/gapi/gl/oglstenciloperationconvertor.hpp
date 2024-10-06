#ifndef SWAY_GAPI_GL_OGLSTENCILOPERATIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLSTENCILOPERATIONCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/stenciloperations.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLStencilOperationConvertor final {
public:
  static auto toGLenum(StencilOp::Enum operation) -> GLenum {
    switch (operation) {
      case StencilOp::Enum::KEEP:
        return GL_KEEP;
      case StencilOp::Enum::ZERO:
        return GL_ZERO;
      case StencilOp::Enum::REPLACE:
        return GL_REPLACE;
      case StencilOp::Enum::INCREMENT:
        return GL_INCR;
      case StencilOp::Enum::INCREMENT_WRAP:
        return GL_INCR_WRAP;
      case StencilOp::Enum::DECREMENT:
        return GL_DECR;
      case StencilOp::Enum::DECREMENT_WRAP:
        return GL_DECR_WRAP;
      case StencilOp::Enum::INVERT:
        return GL_INVERT;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum operation) -> StencilOp::Enum {
    switch (operation) {
      case GL_KEEP:
        return StencilOp::Enum::KEEP;
      case GL_ZERO:
        return StencilOp::Enum::ZERO;
      case GL_REPLACE:
        return StencilOp::Enum::REPLACE;
      case GL_INCR:
        return StencilOp::Enum::INCREMENT;
      case GL_INCR_WRAP:
        return StencilOp::Enum::INCREMENT_WRAP;
      case GL_DECR:
        return StencilOp::Enum::DECREMENT;
      case GL_DECR_WRAP:
        return StencilOp::Enum::DECREMENT_WRAP;
      case GL_INVERT:
        return StencilOp::Enum::INVERT;
      default:
        return StencilOp::Enum::NONE;
    }
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLSTENCILOPERATIONCONVERTOR_HPP
