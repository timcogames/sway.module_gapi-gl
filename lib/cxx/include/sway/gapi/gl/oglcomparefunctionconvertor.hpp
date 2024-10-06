#ifndef SWAY_GAPI_GL_OGLCOMPAREFUNCTIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLCOMPAREFUNCTIONCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLCompareFunctionConvertor final {
public:
  static auto toGLenum(CompareFn::Enum func) -> GLenum {
    switch (func) {
      case CompareFn::Enum::NEVER:
        return GL_NEVER;
      case CompareFn::Enum::ALWAYS:
        return GL_ALWAYS;
      case CompareFn::Enum::LESS:
        return GL_LESS;
      case CompareFn::Enum::LESS_OR_EQUAL:
        return GL_LEQUAL;
      case CompareFn::Enum::EQUAL:
        return GL_EQUAL;
      case CompareFn::Enum::NOT_EQUAL:
        return GL_NOTEQUAL;
      case CompareFn::Enum::GREATER_OR_EQUAL:
        return GL_GEQUAL;
      case CompareFn::Enum::GREATER:
        return GL_GREATER;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum func) -> CompareFn::Enum {
    switch (func) {
      case GL_NEVER:
        return CompareFn::Enum::NEVER;
      case GL_ALWAYS:
        return CompareFn::Enum::ALWAYS;
      case GL_LESS:
        return CompareFn::Enum::LESS;
      case GL_LEQUAL:
        return CompareFn::Enum::LESS_OR_EQUAL;
      case GL_EQUAL:
        return CompareFn::Enum::EQUAL;
      case GL_NOTEQUAL:
        return CompareFn::Enum::NOT_EQUAL;
      case GL_GEQUAL:
        return CompareFn::Enum::GREATER_OR_EQUAL;
      case GL_GREATER:
        return CompareFn::Enum::GREATER;
      default:
        return CompareFn::Enum::NONE;
    }
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLCOMPAREFUNCTIONCONVERTOR_HPP
