#ifndef SWAY_GAPI_GL_WRAP_OGLTEXTUREHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLTEXTUREHELPER_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>
#include <sway/gapi/pixelformats.hpp>
#include <sway/gapi/texturetargets.hpp>
#include <sway/math.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLTextureHelper {
public:
  OGLTextureHelper();

  DECLARE_GENERIC_MEMBER(void, OGLTextureHelper, generateTextures, s32_t, u32_t *)
  void EMU_GenerateTextures(s32_t num, u32_t *textures);
  void STD_GenerateTextures(s32_t num, u32_t *textures);
  void EXT_GenerateTextures(s32_t num, u32_t *textures);

  DECLARE_GENERIC_MEMBER(void, OGLTextureHelper, bindTexture, TextureTarget, std::optional<u32_t>)
  void EMU_BindTexture(TextureTarget target, std::optional<u32_t> texId);
  void STD_BindTexture(TextureTarget target, std::optional<u32_t> texId);
  void EXT_BindTexture(TextureTarget target, std::optional<u32_t> texId);

  DECLARE_GENERIC_MEMBER(void, OGLTextureHelper, textureImage2D, TextureTarget, s32_t, PixelFormat, math::size2i_t,
      s32_t, PixelFormat, core::ValueDataType, const void *)
  void EMU_TextureImage2D(TextureTarget target, s32_t level, PixelFormat internalFormat, math::size2i_t size,
      s32_t border, PixelFormat format, core::ValueDataType type, const void *pixels);
  void STD_TextureImage2D(TextureTarget target, s32_t level, PixelFormat internalFormat, math::size2i_t size,
      s32_t border, PixelFormat format, core::ValueDataType type, const void *pixels);
  void EXT_TextureImage2D(TextureTarget target, s32_t level, PixelFormat internalFormat, math::size2i_t size,
      s32_t border, PixelFormat format, core::ValueDataType type, const void *pixels);

  DECLARE_GENERIC_MEMBER(void, OGLTextureHelper, setActiveTexture, s32_t)
  void EMU_SetActiveTexture(s32_t slot);
  void STD_SetActiveTexture(s32_t slot);
  void ARB_SetActiveTexture(s32_t slot);

  DECLARE_GENERIC_MEMBER(void, OGLTextureHelper, setTextureParamI, TextureTarget, u32_t, s32_t)
  void EMU_SetTextureParamI(TextureTarget target, u32_t pname, s32_t param);
  void STD_SetTextureParamI(TextureTarget target, u32_t pname, s32_t param);
  void EXT_SetTextureParamI(TextureTarget target, u32_t pname, s32_t param);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLTEXTUREHELPER_HPP
