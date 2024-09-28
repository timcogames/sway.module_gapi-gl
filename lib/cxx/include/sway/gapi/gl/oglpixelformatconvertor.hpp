#ifndef SWAY_GAPI_GL_OGLPIXELFORMATCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLPIXELFORMATCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLPixelFormatConvertor final {
  static auto toGLenum(PixelFormat fmt) -> GLenum {
    switch (fmt) {
      case PixelFormat::R:
        return GL_RED;
      case PixelFormat::R32F:
        return GL_R32F;
      case PixelFormat::RG:
        return GL_RG;
      case PixelFormat::RGB:
        return GL_RGB;
      case PixelFormat::RGB8:
        return GL_RGB8;
      case PixelFormat::RGBA:
        return GL_RGBA;
      case PixelFormat::RGBA8:
        return GL_RGBA8;
      case PixelFormat::RGBA32F:
      case PixelFormat::HDR:
        return GL_RGBA32F;
      case PixelFormat::D24:
        return GL_DEPTH_COMPONENT24;
      case PixelFormat::D24S8:
        return GL_DEPTH24_STENCIL8;
      case PixelFormat::LUMINANCE:
        return GL_LUMINANCE;
      case PixelFormat::LUMINANCE_ALPHA:
        return GL_LUMINANCE_ALPHA;
      case PixelFormat::BGR:
        return GL_BGR;
      case PixelFormat::BGRA:
        return GL_BGRA;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum fmt) -> PixelFormat {
    switch (fmt) {
      case GL_RED:
        return PixelFormat::R;
      case GL_R32F:
        return PixelFormat::R32F;
      case GL_RG:
        return PixelFormat::RG;
      case GL_RGB:
        return PixelFormat::RGB;
      case GL_RGB8:
        return PixelFormat::RGB8;
      case GL_RGBA:
        return PixelFormat::RGBA;
      case GL_RGBA8:
        return PixelFormat::RGBA8;
      case GL_RGBA32F:
        return PixelFormat::RGBA32F;
      // case GL_RGBA32F:
      //   return PixelFormat::HDR;
      case GL_DEPTH_COMPONENT24:
        return PixelFormat::D24;
      case GL_DEPTH24_STENCIL8:
        return PixelFormat::D24S8;
      case GL_LUMINANCE:
        return PixelFormat::LUMINANCE;
      case GL_LUMINANCE_ALPHA:
        return PixelFormat::LUMINANCE_ALPHA;
      case GL_BGR:
        return PixelFormat::BGR;
      case GL_BGRA:
        return PixelFormat::BGRA;
      default:
        return PixelFormat::UNKNOWN;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLPIXELFORMATCONVERTOR_HPP
