#ifndef SWAY_GAPI_GL_OGLCULLFACECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLCULLFACECONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLCullFaceConvertor final {
public:
  static auto toGLenum(CullFace face) -> GLenum {
    switch (face) {
      case CullFace::BACK:
        return GL_BACK;
      case CullFace::FRONT:
        return GL_FRONT;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum face) -> CullFace {
    switch (face) {
      case GL_BACK:
        return CullFace::BACK;
      case GL_FRONT:
        return CullFace::FRONT;
      default:
        return CullFace::UNDEF;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLCULLFACECONVERTOR_HPP
