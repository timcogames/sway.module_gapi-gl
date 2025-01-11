#ifndef SWAY_GAPI_GL_OGLGENERICSHADERTYPECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLGENERICSHADERTYPECONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/buffertargets.hpp>
#include <sway/gapi/gl/prereqs.hpp>

namespace sway::gapi {

class OGLGenericShaderTypeConvertor final {
public:
  static auto toGLenum(ShaderType::Enum type) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
    switch (type) {
      case ShaderType::Enum::VERT:
        return GL_VERTEX_SHADER;
      case ShaderType::Enum::FRAG:
        return GL_FRAGMENT_SHADER;
      default:
        return GL_INVALID_INDEX;
    }
#else
    switch (type) {
      case ShaderType::Enum::VERT:
        return GL_VERTEX_SHADER_ARB;
      case ShaderType::Enum::FRAG:
        return GL_FRAGMENT_SHADER_ARB;
      default:
        return GL_INVALID_INDEX;
    }
#endif
  }
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_OGLGENERICSHADERTYPECONVERTOR_HPP
