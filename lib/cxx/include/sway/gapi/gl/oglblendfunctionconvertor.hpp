#ifndef SWAY_GAPI_GL_OGLBLENDFUNCTIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBLENDFUNCTIONCONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLBlendFunctionConvertor final {
public:
  static auto toGLenum(BlendFn::Enum func) -> GLenum {
    switch (func) {
      case BlendFn::Enum::ZERO:
        return GL_ZERO;
      case BlendFn::Enum::ONE:
        return GL_ONE;
      case BlendFn::Enum::SRC_COLOR:
        return GL_SRC_COLOR;
      case BlendFn::Enum::ONE_MINUS_SRC_COLOR:
        return GL_ONE_MINUS_SRC_COLOR;
      case BlendFn::Enum::DST_COLOR:
        return GL_DST_COLOR;
      case BlendFn::Enum::ONE_MINUS_DST_COLOR:
        return GL_ONE_MINUS_DST_COLOR;
      case BlendFn::Enum::SRC_ALPHA:
        return GL_SRC_ALPHA;
      case BlendFn::Enum::ONE_MINUS_SRC_ALPHA:
        return GL_ONE_MINUS_SRC_ALPHA;
      case BlendFn::Enum::DST_ALPHA:
        return GL_DST_ALPHA;
      case BlendFn::Enum::ONE_MINUS_DST_ALPHA:
        return GL_ONE_MINUS_DST_ALPHA;
      case BlendFn::Enum::SRC_ALPHA_SATURATE:
        return GL_SRC_ALPHA_SATURATE;
      default:
        return 0;
        // throw std::runtime_error("Unknown function: " + std::to_string(func));
    }
  }

  static auto fromGLenum(GLenum func) -> BlendFn::Enum {
    switch (func) {
      case GL_ZERO:
        return BlendFn::Enum::ZERO;
      case GL_ONE:
        return BlendFn::Enum::ONE;
      case GL_SRC_COLOR:
        return BlendFn::Enum::SRC_COLOR;
      case GL_ONE_MINUS_SRC_COLOR:
        return BlendFn::Enum::ONE_MINUS_SRC_COLOR;
      case GL_DST_COLOR:
        return BlendFn::Enum::DST_COLOR;
      case GL_ONE_MINUS_DST_COLOR:
        return BlendFn::Enum::ONE_MINUS_DST_COLOR;
      case GL_SRC_ALPHA:
        return BlendFn::Enum::SRC_ALPHA;
      case GL_ONE_MINUS_SRC_ALPHA:
        return BlendFn::Enum::ONE_MINUS_SRC_ALPHA;
      case GL_DST_ALPHA:
        return BlendFn::Enum::DST_ALPHA;
      case GL_ONE_MINUS_DST_ALPHA:
        return BlendFn::Enum::ONE_MINUS_DST_ALPHA;
      case GL_SRC_ALPHA_SATURATE:
        return BlendFn::Enum::SRC_ALPHA_SATURATE;
      default:
        return BlendFn::Enum::NONE;
    }
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLBLENDFUNCTIONCONVERTOR_HPP
