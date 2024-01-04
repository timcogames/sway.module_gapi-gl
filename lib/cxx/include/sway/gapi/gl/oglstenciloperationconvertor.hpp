#ifndef SWAY_GAPI_GL_OGLSTENCILOPERATIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLSTENCILOPERATIONCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/stenciloperations.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLStencilOperationConvertor final {
public:
  static auto toGLenum(StencilOperation operation) -> GLenum {
    switch (operation) {
      case StencilOperation::KEEP:
        return GL_KEEP;
      case StencilOperation::ZERO:
        return GL_ZERO;
      case StencilOperation::REPLACE:
        return GL_REPLACE;
      case StencilOperation::INCREMENT:
        return GL_INCR;
      case StencilOperation::INCREMENT_WRAP:
        return GL_INCR_WRAP;
      case StencilOperation::DECREMENT:
        return GL_DECR;
      case StencilOperation::DECREMENT_WRAP:
        return GL_DECR_WRAP;
      case StencilOperation::INVERT:
        return GL_INVERT;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum operation) -> StencilOperation {
    switch (operation) {
      case GL_KEEP:
        return StencilOperation::KEEP;
      case GL_ZERO:
        return StencilOperation::ZERO;
      case GL_REPLACE:
        return StencilOperation::REPLACE;
      case GL_INCR:
        return StencilOperation::INCREMENT;
      case GL_INCR_WRAP:
        return StencilOperation::INCREMENT_WRAP;
      case GL_DECR:
        return StencilOperation::DECREMENT;
      case GL_DECR_WRAP:
        return StencilOperation::DECREMENT_WRAP;
      case GL_INVERT:
        return StencilOperation::INVERT;
      default:
        return StencilOperation::UNDEF;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTENCILOPERATIONCONVERTOR_HPP
