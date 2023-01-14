#ifndef SWAY_GAPI_GL_WRAP_OGLTEXTUREHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLTEXTUREHELPER_HPP

#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLTextureHelper {
public:
  OGLTextureHelper();

  DECLARE_GENERIC_MEMBER(void, OGLTextureHelper, generateTextures, s32_t, u32_t *)
  void EMU_GenerateTextures(s32_t num, u32_t *textures);
  void STD_GenerateTextures(s32_t num, u32_t *textures);
  void EXT_GenerateTextures(s32_t num, u32_t *textures);

  DECLARE_GENERIC_MEMBER(void, OGLTextureHelper, bindTexture, u32_t, std::optional<u32_t>)
  void EMU_BindTexture(u32_t target, std::optional<u32_t> texId);
  void STD_BindTexture(u32_t target, std::optional<u32_t> texId);
  void EXT_BindTexture(u32_t target, std::optional<u32_t> texId);

  DECLARE_GENERIC_MEMBER(
      void, OGLTextureHelper, TextureImage2D, s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, const void *)
  void EMU_TextureImage2D(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height, s32_t border,
      s32_t format, s32_t type, const void *pixels);
  void STD_TextureImage2D(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height, s32_t border,
      s32_t format, s32_t type, const void *pixels);
  void EXT_TextureImage2D(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height, s32_t border,
      s32_t format, s32_t type, const void *pixels);

  DECLARE_GENERIC_MEMBER(void, OGLTextureHelper, setActiveTexture, s32_t)
  void EMU_setActiveTexture(s32_t slot);
  void STD_setActiveTexture(s32_t slot);
  void ARB_setActiveTexture(s32_t slot);

  DECLARE_GENERIC_MEMBER(void, OGLTextureHelper, setTextureParamI, u32_t, u32_t, s32_t)
  void EMU_setTextureParamI(u32_t target, u32_t pname, s32_t param);
  void STD_setTextureParamI(u32_t target, u32_t pname, s32_t param);
  void EXT_setTextureParamI(u32_t target, u32_t pname, s32_t param);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLTEXTUREHELPER_HPP
