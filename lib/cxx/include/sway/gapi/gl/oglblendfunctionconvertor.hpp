#ifndef SWAY_GAPI_GL_OGLBLENDFUNCTIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBLENDFUNCTIONCONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLBlendFunctionConvertor final {
public:
  static auto toGLenum(BlendFn func) -> GLenum {
    switch (func) {
      case BlendFn::ZERO:
        return GL_ZERO;
      case BlendFn::ONE:
        return GL_ONE;
      case BlendFn::SRC_COLOR:
        return GL_SRC_COLOR;
      case BlendFn::ONE_MINUS_SRC_COLOR:
        return GL_ONE_MINUS_SRC_COLOR;
      case BlendFn::DST_COLOR:
        return GL_DST_COLOR;
      case BlendFn::ONE_MINUS_DST_COLOR:
        return GL_ONE_MINUS_DST_COLOR;
      case BlendFn::SRC_ALPHA:
        return GL_SRC_ALPHA;
      case BlendFn::ONE_MINUS_SRC_ALPHA:
        return GL_ONE_MINUS_SRC_ALPHA;
      case BlendFn::DST_ALPHA:
        return GL_DST_ALPHA;
      case BlendFn::ONE_MINUS_DST_ALPHA:
        return GL_ONE_MINUS_DST_ALPHA;
      case BlendFn::SRC_ALPHA_SATURATE:
        return GL_SRC_ALPHA_SATURATE;
      default:
        return 0;
        // throw std::runtime_error("Unknown function: " + std::to_string(func));
    }
  }

  static auto fromGLenum(GLenum func) -> BlendFn {
    switch (func) {
      case GL_ZERO:
        return BlendFn::ZERO;
      case GL_ONE:
        return BlendFn::ONE;
      case GL_SRC_COLOR:
        return BlendFn::SRC_COLOR;
      case GL_ONE_MINUS_SRC_COLOR:
        return BlendFn::ONE_MINUS_SRC_COLOR;
      case GL_DST_COLOR:
        return BlendFn::DST_COLOR;
      case GL_ONE_MINUS_DST_COLOR:
        return BlendFn::ONE_MINUS_DST_COLOR;
      case GL_SRC_ALPHA:
        return BlendFn::SRC_ALPHA;
      case GL_ONE_MINUS_SRC_ALPHA:
        return BlendFn::ONE_MINUS_SRC_ALPHA;
      case GL_DST_ALPHA:
        return BlendFn::DST_ALPHA;
      case GL_ONE_MINUS_DST_ALPHA:
        return BlendFn::ONE_MINUS_DST_ALPHA;
      case GL_SRC_ALPHA_SATURATE:
        return BlendFn::SRC_ALPHA_SATURATE;
      default:
        return BlendFn::NONE;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLBLENDFUNCTIONCONVERTOR_HPP
