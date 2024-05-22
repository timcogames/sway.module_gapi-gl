#ifndef SWAY_GAPI_GL_OGLCOMPAREFUNCTIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLCOMPAREFUNCTIONCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLCompareFunctionConvertor final {
public:
  static auto toGLenum(CompareFn func) -> GLenum {
    switch (func) {
      case CompareFn::NEVER:
        return GL_NEVER;
      case CompareFn::ALWAYS:
        return GL_ALWAYS;
      case CompareFn::LESS:
        return GL_LESS;
      case CompareFn::LESS_OR_EQUAL:
        return GL_LEQUAL;
      case CompareFn::EQUAL:
        return GL_EQUAL;
      case CompareFn::NOT_EQUAL:
        return GL_NOTEQUAL;
      case CompareFn::GREATER_OR_EQUAL:
        return GL_GEQUAL;
      case CompareFn::GREATER:
        return GL_GREATER;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum func) -> CompareFn {
    switch (func) {
      case GL_NEVER:
        return CompareFn::NEVER;
      case GL_ALWAYS:
        return CompareFn::ALWAYS;
      case GL_LESS:
        return CompareFn::LESS;
      case GL_LEQUAL:
        return CompareFn::LESS_OR_EQUAL;
      case GL_EQUAL:
        return CompareFn::EQUAL;
      case GL_NOTEQUAL:
        return CompareFn::NOT_EQUAL;
      case GL_GEQUAL:
        return CompareFn::GREATER_OR_EQUAL;
      case GL_GREATER:
        return CompareFn::GREATER;
      default:
        return CompareFn::NONE;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLCOMPAREFUNCTIONCONVERTOR_HPP
