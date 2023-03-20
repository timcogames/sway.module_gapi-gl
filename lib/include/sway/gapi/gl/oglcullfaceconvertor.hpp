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
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLCULLFACECONVERTOR_HPP
