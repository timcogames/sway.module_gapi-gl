#ifndef SWAY_GAPI_GL_OGLTEXTURETARGETCONVERTOR_HPP
#define SWAY_GAPI_GL_OGLTEXTURETARGETCONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

struct OGLTextureTargetConvertor final {
  static auto toGLenum(TextureTarget::Enum target) -> GLenum {
    switch (target) {
      case TextureTarget::Enum::TEX_2D:
        return GL_TEXTURE_2D;
      case TextureTarget::Enum::TEX_2D_ARRAY:
        return GL_TEXTURE_2D_ARRAY;
      case TextureTarget::Enum::RECT:
        return GL_TEXTURE_RECTANGLE_ARB;
      case TextureTarget::Enum::CUBE_MAP:
        return GL_TEXTURE_CUBE_MAP;
      default:
        return 0;
    }
  }

  static auto fromGLenum(GLenum target) -> TextureTarget::Enum {
    switch (target) {
      case GL_TEXTURE_2D:
        return TextureTarget::Enum::TEX_2D;
      case GL_TEXTURE_2D_ARRAY:
        return TextureTarget::Enum::TEX_2D_ARRAY;
      case GL_TEXTURE_RECTANGLE_ARB:
        return TextureTarget::Enum::RECT;
      case GL_TEXTURE_CUBE_MAP:
        return TextureTarget::Enum::CUBE_MAP;
      default:
        return TextureTarget::Enum::NONE;
    }
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLTEXTURETARGETCONVERTOR_HPP
