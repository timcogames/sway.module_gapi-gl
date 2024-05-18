#ifndef SWAY_GAPI_GL_OGLGENERICSHADERTYPECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLGENERICSHADERTYPECONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/buffertargets.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLGenericShaderTypeConvertor final {
public:
  static auto toGLenum(ShaderType type) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
    switch (type) {
      case ShaderType::VERT:
        return GL_VERTEX_SHADER;
      case ShaderType::FRAG:
        return GL_FRAGMENT_SHADER;
      default:
        return GL_INVALID_INDEX;
    }
#else
    switch (type) {
      case ShaderType::VERT:
        return GL_VERTEX_SHADER_ARB;
      case ShaderType::FRAG:
        return GL_FRAGMENT_SHADER_ARB;
      default:
        return GL_INVALID_INDEX;
    }
#endif
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLGENERICSHADERTYPECONVERTOR_HPP
