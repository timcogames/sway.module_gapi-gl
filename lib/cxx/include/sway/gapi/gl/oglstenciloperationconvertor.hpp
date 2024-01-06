#ifndef SWAY_GAPI_GL_OGLSTENCILOPERATIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLSTENCILOPERATIONCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/stenciloperations.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLStencilOperationConvertor final {
public:
  static auto toGLenum(StencilOp operation) -> GLenum {
    switch (operation) {
      case StencilOp::KEEP:
        return GL_KEEP;
      case StencilOp::ZERO:
        return GL_ZERO;
      case StencilOp::REPLACE:
        return GL_REPLACE;
      case StencilOp::INCREMENT:
        return GL_INCR;
      case StencilOp::INCREMENT_WRAP:
        return GL_INCR_WRAP;
      case StencilOp::DECREMENT:
        return GL_DECR;
      case StencilOp::DECREMENT_WRAP:
        return GL_DECR_WRAP;
      case StencilOp::INVERT:
        return GL_INVERT;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum operation) -> StencilOp {
    switch (operation) {
      case GL_KEEP:
        return StencilOp::KEEP;
      case GL_ZERO:
        return StencilOp::ZERO;
      case GL_REPLACE:
        return StencilOp::REPLACE;
      case GL_INCR:
        return StencilOp::INCREMENT;
      case GL_INCR_WRAP:
        return StencilOp::INCREMENT_WRAP;
      case GL_DECR:
        return StencilOp::DECREMENT;
      case GL_DECR_WRAP:
        return StencilOp::DECREMENT_WRAP;
      case GL_INVERT:
        return StencilOp::INVERT;
      default:
        return StencilOp::UNDEF;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTENCILOPERATIONCONVERTOR_HPP
