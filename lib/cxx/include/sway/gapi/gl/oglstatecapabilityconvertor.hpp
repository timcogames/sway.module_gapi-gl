#ifndef SWAY_GAPI_GL_OGLSTATECAPABILITYCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLSTATECAPABILITYCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLStateCapabilityConvertor final {
public:
  static auto toGLenum(StateCapability::Enum cap) -> GLenum {
    switch (cap) {
      case StateCapability::Enum::BLEND:
        return GL_BLEND;
      case StateCapability::Enum::CULL_FACE:
        return GL_CULL_FACE;
      case StateCapability::Enum::ALPHA_TEST:
        return GL_ALPHA_TEST;
      case StateCapability::Enum::DEPTH_TEST:
        return GL_DEPTH_TEST;
      case StateCapability::Enum::SCISSOR_TEST:
        return GL_SCISSOR_TEST;
      case StateCapability::Enum::STENCIL_TEST:
        return GL_STENCIL_TEST;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum cap) -> StateCapability::Enum {
    switch (cap) {
      case GL_BLEND:
        return StateCapability::Enum::BLEND;
      case GL_CULL_FACE:
        return StateCapability::Enum::CULL_FACE;
      case GL_DEPTH_TEST:
        return StateCapability::Enum::DEPTH_TEST;
      case GL_SCISSOR_TEST:
        return StateCapability::Enum::SCISSOR_TEST;
      case GL_STENCIL_TEST:
        return StateCapability::Enum::STENCIL_TEST;
      default:
        return StateCapability::Enum::NONE;
    }
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLSTATECAPABILITYCONVERTOR_HPP
