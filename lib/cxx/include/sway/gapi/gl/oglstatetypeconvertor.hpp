#ifndef SWAY_GAPI_GL_OGLSTATETYPECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLSTATETYPECONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLStateTypeConvertor final {
public:
  static auto toGLenum(StateType type) -> GLenum {
    switch (type) {
      case StateType::BLEND:
        return GL_BLEND;
      case StateType::CULL_FACE:
        return GL_CULL_FACE;
      case StateType::DEPTH_TEST:
        return GL_DEPTH_TEST;
      case StateType::SCISSOR_TEST:
        return GL_SCISSOR_TEST;
      case StateType::STENCIL_TEST:
        return GL_STENCIL_TEST;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum type) -> StateType {
    switch (type) {
      case GL_BLEND:
        return StateType::BLEND;
      case GL_CULL_FACE:
        return StateType::CULL_FACE;
      case GL_DEPTH_TEST:
        return StateType::DEPTH_TEST;
      case GL_SCISSOR_TEST:
        return StateType::SCISSOR_TEST;
      case GL_STENCIL_TEST:
        return StateType::STENCIL_TEST;
      default:
        return StateType::UNDEF;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTATETYPECONVERTOR_HPP
