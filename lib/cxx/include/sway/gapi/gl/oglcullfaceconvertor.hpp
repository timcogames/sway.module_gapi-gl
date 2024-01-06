#ifndef SWAY_GAPI_GL_OGLCULLFACECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLCULLFACECONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLCullFaceConvertor final {
  static auto current() -> CullFace {
    return OGLCullFaceConvertor::fromGLenum(TypeUtils::getU32Params(GL_CULL_FACE_MODE));
  }

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
        return CullFace::DISABLED;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLCULLFACECONVERTOR_HPP
