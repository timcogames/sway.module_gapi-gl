#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/oglpixelformatconvertor.hpp>
#include <sway/gapi/gl/ogltexturetargetconvertor.hpp>
#include <sway/gapi/gl/wrap/ogltextureextension.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLTextureHelper::OGLTextureHelper() {
#ifdef _STUB
  generateTextures_ = &OGLTextureHelper::EMU_GenerateTextures;
  bindTexture_ = &OGLTextureHelper::EMU_BindTexture;
  textureImage2D_ = &OGLTextureHelper::EMU_TextureImage2D;
  texSubImage2D_ = &OGLTextureHelper::EMU_TexSubImage2D;
  setActiveTexture_ = &OGLTextureHelper::EMU_SetActiveTexture;
  setTextureParamI_ = &OGLTextureHelper::EMU_SetTextureParamI;
#else

  const auto *extensions = OGLCapability::getExtensions();

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_texture_object")) {
    generateTextures_ = &OGLTextureHelper::EXT_GenerateTextures;
    bindTexture_ = &OGLTextureHelper::EXT_BindTexture;
  } else {
    generateTextures_ = &OGLTextureHelper::STD_GenerateTextures;
    bindTexture_ = &OGLTextureHelper::STD_BindTexture;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_direct_state_access")) {
    textureImage2D_ = &OGLTextureHelper::EXT_TextureImage2D;
  } else {
    textureImage2D_ = &OGLTextureHelper::STD_TextureImage2D;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_subtexture")) {
    texSubImage2D_ = &OGLTextureHelper::EXT_TexSubImage2D;
  } else {
    texSubImage2D_ = &OGLTextureHelper::STD_TexSubImage2D;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_multitexture")) {
    setActiveTexture_ = &OGLTextureHelper::ARB_SetActiveTexture;
  } else {
    setActiveTexture_ = &OGLTextureHelper::STD_SetActiveTexture;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_texture_integer")) {
    setTextureParamI_ = &OGLTextureHelper::EXT_SetTextureParamI;
  } else {
    setTextureParamI_ = &OGLTextureHelper::STD_SetTextureParamI;
  }

#endif
}

void OGLTextureHelper::EMU_GenerateTextures([[maybe_unused]] s32_t num, [[maybe_unused]] u32_t *textures) {}

void OGLTextureHelper::STD_GenerateTextures(s32_t num, u32_t *textures) { glGenTextures(num, textures); }

void OGLTextureHelper::EXT_GenerateTextures(s32_t num, u32_t *textures) {
  OGLTextureExtension::glGenTexturesEXT(num, textures);
}

void OGLTextureHelper::EMU_BindTexture(
    [[maybe_unused]] TextureTarget target, [[maybe_unused]] std::optional<u32_t> texId) {}

void OGLTextureHelper::STD_BindTexture(TextureTarget target, std::optional<u32_t> texId) {
  glBindTexture(OGLTextureTargetConvertor::toGLenum(target), texId.value());
}

void OGLTextureHelper::EXT_BindTexture(TextureTarget target, std::optional<u32_t> texId) {
  OGLTextureExtension::glBindTextureEXT(OGLTextureTargetConvertor::toGLenum(target), texId.value());
}

void OGLTextureHelper::EMU_TextureImage2D([[maybe_unused]] TextureTarget target, [[maybe_unused]] s32_t level,
    [[maybe_unused]] PixelFormat internalFormat, [[maybe_unused]] math::size2i_t size, [[maybe_unused]] s32_t border,
    [[maybe_unused]] PixelFormat frm, [[maybe_unused]] core::ValueDataType type, [[maybe_unused]] const void *pixels) {}

void OGLTextureHelper::STD_TextureImage2D(TextureTarget target, s32_t level, PixelFormat internalFormat,
    math::size2i_t size, s32_t border, PixelFormat frm, core::ValueDataType type, const void *pixels) {
  if (target != TextureTarget::TEX_2D) {
    return;
  }

  glTexImage2D(OGLTextureTargetConvertor::toGLenum(target), level, OGLPixelFormatConvertor::toGLenum(internalFormat),
      size.getW(), size.getH(), border, OGLPixelFormatConvertor::toGLenum(frm), TypeUtils::toGL(type), pixels);
}

void OGLTextureHelper::EXT_TextureImage2D(TextureTarget target, s32_t level, PixelFormat internalFormat,
    math::size2i_t size, s32_t border, PixelFormat frm, core::ValueDataType type, const void *pixels) {
  if (target != TextureTarget::TEX_2D) {
    return;
  }

  OGLTextureExtension::glTextureImage2DEXT(OGLTextureTargetConvertor::toGLenum(target), level,
      OGLPixelFormatConvertor::toGLenum(internalFormat), size.getW(), size.getH(), border,
      OGLPixelFormatConvertor::toGLenum(frm), TypeUtils::toGL(type), pixels);
}

void OGLTextureHelper::EMU_TexSubImage2D([[maybe_unused]] TextureTarget target, [[maybe_unused]] s32_t level,
    [[maybe_unused]] s32_t xoffset, [[maybe_unused]] s32_t yoffset, [[maybe_unused]] s32_t width,
    [[maybe_unused]] s32_t height, [[maybe_unused]] PixelFormat frm, [[maybe_unused]] core::ValueDataType type,
    [[maybe_unused]] const void *pixels) {}

void OGLTextureHelper::STD_TexSubImage2D(TextureTarget target, s32_t level, s32_t xoffset, s32_t yoffset, s32_t width,
    s32_t height, PixelFormat frm, core::ValueDataType type, const void *pixels) {
  glTexSubImage2D(OGLTextureTargetConvertor::toGLenum(target), level, xoffset, yoffset, width, height,
      OGLPixelFormatConvertor::toGLenum(frm), TypeUtils::toGL(type), pixels);
}

void OGLTextureHelper::EXT_TexSubImage2D(TextureTarget target, s32_t level, s32_t xoffset, s32_t yoffset, s32_t width,
    s32_t height, PixelFormat frm, core::ValueDataType type, const void *pixels) {
  OGLTextureExtension::glTexSubImage2DEXT(OGLTextureTargetConvertor::toGLenum(target), level, xoffset, yoffset, width,
      height, OGLPixelFormatConvertor::toGLenum(frm), TypeUtils::toGL(type), pixels);
}

void OGLTextureHelper::EMU_SetActiveTexture([[maybe_unused]] s32_t slot) {}

void OGLTextureHelper::STD_SetActiveTexture(s32_t slot) { glActiveTexture(slot); }

void OGLTextureHelper::ARB_SetActiveTexture(s32_t slot) { OGLTextureExtension::glActiveTextureARB(slot); }

void OGLTextureHelper::EMU_SetTextureParamI(
    [[maybe_unused]] TextureTarget target, [[maybe_unused]] u32_t pname, [[maybe_unused]] s32_t param) {}

void OGLTextureHelper::STD_SetTextureParamI(TextureTarget target, u32_t pname, s32_t param) {
  glTexParameteri(OGLTextureTargetConvertor::toGLenum(target), pname, param);
}

void OGLTextureHelper::EXT_SetTextureParamI(TextureTarget target, u32_t pname, s32_t param) {
  OGLTextureExtension::glTexParameterIivEXT(OGLTextureTargetConvertor::toGLenum(target), pname, (const s32_t *)&param);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
