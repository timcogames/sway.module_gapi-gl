#ifndef SWAY_GAPI_GL_OGLBLENDEQUATIONCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLBLENDEQUATIONCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/blendequations.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLBlendEquationConvertor final {
public:
  static auto toGLenum(BlendEq::Enum equation) -> GLenum {
    switch (equation) {
      case BlendEq::Enum::ADD:
        return GL_FUNC_ADD;
      case BlendEq::Enum::SUBTRACT:
        return GL_FUNC_SUBTRACT;
      case BlendEq::Enum::REVERSE_SUBTRACT:
        return GL_FUNC_REVERSE_SUBTRACT;
      case BlendEq::Enum::MIN:
        return GL_MIN;
      case BlendEq::Enum::MAX:
        return GL_MAX;
      default:
        // throw std::runtime_error("Unknown equation: " + std::to_string(eqn));
        return 0;
    }
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLBLENDEQUATIONCONVERTOR_HPP
