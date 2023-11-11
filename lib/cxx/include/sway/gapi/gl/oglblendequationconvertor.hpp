#ifndef SWAY_GAPI_GL_OGLBLENDEQUATIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBLENDEQUATIONCONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLBlendEquationConvertor final {
public:
  static auto toGLenum(BlendEquation eqn) -> GLenum {
    switch (eqn) {
      case BlendEquation::ADD:
        return GL_FUNC_ADD;
      case BlendEquation::SUBTRACT:
        return GL_FUNC_SUBTRACT;
      case BlendEquation::REVERSE_SUBTRACT:
        return GL_FUNC_REVERSE_SUBTRACT;
      case BlendEquation::MIN:
        return GL_MIN;
      case BlendEquation::MAX:
        return GL_MAX;
      default:
        // throw std::runtime_error("Unknown equation: " + std::to_string(eqn));
        return 0;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLBLENDEQUATIONCONVERTOR_HPP
