#ifndef SWAY_GAPI_GL_OGLFRONTFACECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLFRONTFACECONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLFrontFaceConvertor final {
  static auto current() -> FrontFace {
    return OGLFrontFaceConvertor::fromGLenum(TypeUtils::getU32Params(GL_FRONT_FACE));
  }

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

  static auto fromGLenum(GLenum face) -> FrontFace {
    switch (face) {
      case GL_CW:
        return FrontFace::CLOCK_WISE;
      case GL_CCW:
        return FrontFace::COUNTER_CLOCK_WISE;
      default:
        return FrontFace::NONE;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLFRONTFACECONVERTOR_HPP
