#ifndef SWAY_GAPI_GL_OGLCOMPAREFUNCTIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLCOMPAREFUNCTIONCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLCompareFunctionConvertor final {
public:
  static auto toGLenum(CompareFunction function) -> GLenum {
    switch (function) {
      case CompareFunction::NEVER:
        return GL_NEVER;
      case CompareFunction::ALWAYS:
        return GL_ALWAYS;
      case CompareFunction::LESS:
        return GL_LESS;
      case CompareFunction::LESS_OR_EQUAL:
        return GL_LEQUAL;
      case CompareFunction::EQUAL:
        return GL_EQUAL;
      case CompareFunction::NOT_EQUAL:
        return GL_NOTEQUAL;
      case CompareFunction::GREATER_OR_EQUAL:
        return GL_GEQUAL;
      case CompareFunction::GREATER:
        return GL_GREATER;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum func) -> CompareFunction {
    switch (func) {
      case GL_NEVER:
        return CompareFunction::NEVER;
      case GL_ALWAYS:
        return CompareFunction::ALWAYS;
      case GL_LESS:
        return CompareFunction::LESS;
      case GL_LEQUAL:
        return CompareFunction::LESS_OR_EQUAL;
      case GL_EQUAL:
        return CompareFunction::EQUAL;
      case GL_NOTEQUAL:
        return CompareFunction::NOT_EQUAL;
      case GL_GEQUAL:
        return CompareFunction::GREATER_OR_EQUAL;
      case GL_GREATER:
        return CompareFunction::GREATER;
      default:
        return CompareFunction::UNDEF;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLCOMPAREFUNCTIONCONVERTOR_HPP
