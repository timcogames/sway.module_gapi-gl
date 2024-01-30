#ifndef SWAY_GAPI_GL_OGLTEXTURETARGETCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLTEXTURETARGETCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLTextureTargetConvertor final {
  static auto toGLenum(TextureTarget target) -> GLenum {
    switch (target) {
      case TextureTarget::TEX_2D:
        return GL_TEXTURE_2D;
      case TextureTarget::TEX_2D_ARRAY:
        return GL_TEXTURE_2D_ARRAY;
      case TextureTarget::RECT:
        return GL_TEXTURE_RECTANGLE_ARB;
      case TextureTarget::CUBE_MAP:
        return GL_TEXTURE_CUBE_MAP;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum target) -> TextureTarget {
    switch (target) {
      case GL_TEXTURE_2D:
        return TextureTarget::TEX_2D;
      case GL_TEXTURE_2D_ARRAY:
        return TextureTarget::TEX_2D_ARRAY;
      case GL_TEXTURE_RECTANGLE_ARB:
        return TextureTarget::RECT;
      case GL_TEXTURE_CUBE_MAP:
        return TextureTarget::CUBE_MAP;
      default:
        return TextureTarget::UNKNOWN;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLTEXTURETARGETCONVERTOR_HPP
