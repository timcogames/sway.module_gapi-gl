#ifndef SWAY_GAPI_GL_OGLFRONTFACECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLFRONTFACECONVERTOR_HPP

#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

struct OGLFrontFaceConvertor final {
  static auto current() -> FrontFace::Enum {
    return OGLFrontFaceConvertor::fromGLenum(TypeUtils::getU32Params(GL_FRONT_FACE));
  }

  static auto toGLenum(FrontFace::Enum face) -> GLenum {
    switch (face) {
      case FrontFace::Enum::CLOCK_WISE:
        return GL_CW;
      case FrontFace::Enum::COUNTER_CLOCK_WISE:
        return GL_CCW;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum face) -> FrontFace::Enum {
    switch (face) {
      case GL_CW:
        return FrontFace::Enum::CLOCK_WISE;
      case GL_CCW:
        return FrontFace::Enum::COUNTER_CLOCK_WISE;
      default:
        return FrontFace::Enum::NONE;
    }
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLFRONTFACECONVERTOR_HPP
