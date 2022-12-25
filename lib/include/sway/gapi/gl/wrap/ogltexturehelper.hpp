#ifndef SWAY_GAPI_GL_WRAP_OGLTEXTUREHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLTEXTUREHELPER_HPP

#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLTextureHelper {
public:
  OGLTextureHelper();

  DECLARE_GENERIC_MEMBER(
      OGLTextureHelper, TextureImage2D, void, s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, const void *)
  auto EMU_TextureImage2D(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height, s32_t border,
      s32_t format, s32_t type, const void *pixels) -> void;
  auto STD_TextureImage2D(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height, s32_t border,
      s32_t format, s32_t type, const void *pixels) -> void;
  auto EXT_TextureImage2D(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height, s32_t border,
      s32_t format, s32_t type, const void *pixels) -> void;

  DECLARE_GENERIC_MEMBER(OGLTextureHelper, setActiveTexture, void, s32_t)
  auto EMU_setActiveTexture(s32_t target) -> void;
  auto STD_setActiveTexture(s32_t target) -> void;
  auto ARB_setActiveTexture(s32_t target) -> void;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLTEXTUREHELPER_HPP
