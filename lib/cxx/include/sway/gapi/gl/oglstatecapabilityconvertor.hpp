#ifndef SWAY_GAPI_GL_OGLSTATECAPABILITYCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLSTATECAPABILITYCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLStateCapabilityConvertor final {
public:
  static auto toGLenum(StateCapability cap) -> GLenum {
    switch (cap) {
      case StateCapability::BLEND:
        return GL_BLEND;
      case StateCapability::CULL_FACE:
        return GL_CULL_FACE;
      case StateCapability::DEPTH_TEST:
        return GL_DEPTH_TEST;
      case StateCapability::SCISSOR_TEST:
        return GL_SCISSOR_TEST;
      case StateCapability::STENCIL_TEST:
        return GL_STENCIL_TEST;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum cap) -> StateCapability {
    switch (cap) {
      case GL_BLEND:
        return StateCapability::BLEND;
      case GL_CULL_FACE:
        return StateCapability::CULL_FACE;
      case GL_DEPTH_TEST:
        return StateCapability::DEPTH_TEST;
      case GL_SCISSOR_TEST:
        return StateCapability::SCISSOR_TEST;
      case GL_STENCIL_TEST:
        return StateCapability::STENCIL_TEST;
      default:
        return StateCapability::NONE;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTATECAPABILITYCONVERTOR_HPP
