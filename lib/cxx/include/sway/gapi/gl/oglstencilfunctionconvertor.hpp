#ifndef SWAY_GAPI_GL_OGLSTENCILFUNCTIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLSTENCILFUNCTIONCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/stencilfunctions.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLStencilFunctionConvertor final {
public:
  static auto toGLenum(StencilFunction function) -> GLenum {
    switch (function) {
      case StencilFunction::NEVER:
        return GL_NEVER;
      case StencilFunction::ALWAYS:
        return GL_ALWAYS;
      case StencilFunction::_LESS:
        return GL_LESS;
      case StencilFunction::LESS_OR_EQUAL:
        return GL_LEQUAL;
      case StencilFunction::EQUAL:
        return GL_EQUAL;
      case StencilFunction::NOT_EQUAL:
        return GL_NOTEQUAL;
      case StencilFunction::GREATER_OR_EQUAL:
        return GL_GEQUAL;
      case StencilFunction::GREATER:
        return GL_GREATER;
      default:
        return 0;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTENCILFUNCTIONCONVERTOR_HPP
