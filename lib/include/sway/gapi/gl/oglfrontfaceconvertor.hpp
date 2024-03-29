#ifndef SWAY_GAPI_GL_OGLFRONTFACECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLFRONTFACECONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLFrontFaceConvertor final {
public:
  static auto toGLenum(FrontFace face) -> GLenum {
    switch (face) {
      case FrontFace::CLOCK_WISE:
        return GL_CW;
      case FrontFace::COUNTER_CLOCK_WISE:
        return GL_CCW;
      default:
        return 0;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLFRONTFACECONVERTOR_HPP
