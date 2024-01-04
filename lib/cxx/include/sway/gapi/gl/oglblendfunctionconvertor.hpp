#ifndef SWAY_GAPI_GL_OGLBLENDFUNCTIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBLENDFUNCTIONCONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLBlendFunctionConvertor final {
public:
  static auto toGLenum(BlendFunction fnc) -> GLenum {
    switch (fnc) {
      case BlendFunction::ZERO:
        return GL_ZERO;
      case BlendFunction::ONE:
        return GL_ONE;
      case BlendFunction::SRC_COLOR:
        return GL_SRC_COLOR;
      case BlendFunction::ONE_MINUS_SRC_COLOR:
        return GL_ONE_MINUS_SRC_COLOR;
      case BlendFunction::DST_COLOR:
        return GL_DST_COLOR;
      case BlendFunction::ONE_MINUS_DST_COLOR:
        return GL_ONE_MINUS_DST_COLOR;
      case BlendFunction::SRC_ALPHA:
        return GL_SRC_ALPHA;
      case BlendFunction::ONE_MINUS_SRC_ALPHA:
        return GL_ONE_MINUS_SRC_ALPHA;
      case BlendFunction::DST_ALPHA:
        return GL_DST_ALPHA;
      case BlendFunction::ONE_MINUS_DST_ALPHA:
        return GL_ONE_MINUS_DST_ALPHA;
      case BlendFunction::SRC_ALPHA_SATURATE:
        return GL_SRC_ALPHA_SATURATE;
      default:
        return 0;
        // throw std::runtime_error("Unknown function: " + std::to_string(func));
    }
  }

  static auto fromGLenum(GLenum func) -> BlendFunction {
    switch (func) {
      case GL_ZERO:
        return BlendFunction::ZERO;
      case GL_ONE:
        return BlendFunction::ONE;
      case GL_SRC_COLOR:
        return BlendFunction::SRC_COLOR;
      case GL_ONE_MINUS_SRC_COLOR:
        return BlendFunction::ONE_MINUS_SRC_COLOR;
      case GL_DST_COLOR:
        return BlendFunction::DST_COLOR;
      case GL_ONE_MINUS_DST_COLOR:
        return BlendFunction::ONE_MINUS_DST_COLOR;
      case GL_SRC_ALPHA:
        return BlendFunction::SRC_ALPHA;
      case GL_ONE_MINUS_SRC_ALPHA:
        return BlendFunction::ONE_MINUS_SRC_ALPHA;
      case GL_DST_ALPHA:
        return BlendFunction::DST_ALPHA;
      case GL_ONE_MINUS_DST_ALPHA:
        return BlendFunction::ONE_MINUS_DST_ALPHA;
      case GL_SRC_ALPHA_SATURATE:
        return BlendFunction::SRC_ALPHA_SATURATE;
      default:
        return BlendFunction::UNDEF;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLBLENDFUNCTIONCONVERTOR_HPP
