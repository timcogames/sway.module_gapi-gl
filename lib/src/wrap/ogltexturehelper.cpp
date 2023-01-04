#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/ogltextureextension.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLTextureHelper::OGLTextureHelper() {
#ifdef _STUB
  generateTextures_ = &OGLTextureHelper::EMU_GenerateTextures;
  bindTexture_ = &OGLTextureHelper::EMU_BindTexture;
  TextureImage2D_ = &OGLTextureHelper::EMU_TextureImage2D;
  setActiveTexture_ = &OGLTextureHelper::EMU_setActiveTexture;
  setTextureParamI_ = &OGLTextureHelper::EMU_setTextureParamI;
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
    TextureImage2D_ = &OGLTextureHelper::EXT_TextureImage2D;
  } else {
    TextureImage2D_ = &OGLTextureHelper::STD_TextureImage2D;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_multitexture")) {
    setActiveTexture_ = &OGLTextureHelper::ARB_setActiveTexture;
  } else {
    setActiveTexture_ = &OGLTextureHelper::STD_setActiveTexture;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_texture_integer")) {
    setTextureParamI_ = &OGLTextureHelper::EXT_setTextureParamI;
  } else {
    setTextureParamI_ = &OGLTextureHelper::STD_setTextureParamI;
  }

#endif
}

void OGLTextureHelper::EMU_GenerateTextures([[maybe_unused]] s32_t num, [[maybe_unused]] u32_t *textures) {}

void OGLTextureHelper::STD_GenerateTextures(s32_t num, u32_t *textures) { glGenTextures(num, textures); }

void OGLTextureHelper::EXT_GenerateTextures(s32_t num, u32_t *textures) {
  OGLTextureExtension::glGenTexturesEXT(num, textures);
}

void OGLTextureHelper::EMU_BindTexture([[maybe_unused]] u32_t target, [[maybe_unused]] std::optional<u32_t> texId) {}

void OGLTextureHelper::STD_BindTexture(u32_t target, std::optional<u32_t> texId) {
  glBindTexture(target, texId.value());
}

void OGLTextureHelper::EXT_BindTexture(u32_t target, std::optional<u32_t> texId) {
  OGLTextureExtension::glBindTextureEXT(target, texId.value());
}

void OGLTextureHelper::EMU_TextureImage2D([[maybe_unused]] s32_t target, [[maybe_unused]] s32_t level,
    [[maybe_unused]] s32_t internalFormat, [[maybe_unused]] s32_t width, [[maybe_unused]] s32_t height,
    [[maybe_unused]] s32_t border, [[maybe_unused]] s32_t format, [[maybe_unused]] s32_t type,
    [[maybe_unused]] const void *pixels) {}

void OGLTextureHelper::STD_TextureImage2D(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height,
    s32_t border, s32_t format, s32_t type, const void *pixels) {
  glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
}

void OGLTextureHelper::EXT_TextureImage2D(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height,
    s32_t border, s32_t format, s32_t type, const void *pixels) {
  OGLTextureExtension::glTextureImage2DEXT(target, level, internalFormat, width, height, border, format, type, pixels);
}

void OGLTextureHelper::EMU_setActiveTexture([[maybe_unused]] std::optional<u32_t> texId) {}

void OGLTextureHelper::STD_setActiveTexture(std::optional<u32_t> texId) { glActiveTexture(texId.value()); }

void OGLTextureHelper::ARB_setActiveTexture(std::optional<u32_t> texId) {
  OGLTextureExtension::glActiveTextureARB(texId.value());
}

void OGLTextureHelper::EMU_setTextureParamI(
    [[maybe_unused]] u32_t target, [[maybe_unused]] u32_t pname, [[maybe_unused]] s32_t param) {}

void OGLTextureHelper::STD_setTextureParamI(u32_t target, u32_t pname, s32_t param) {
  glTexParameteri(target, pname, param);
}

void OGLTextureHelper::EXT_setTextureParamI(u32_t target, u32_t pname, s32_t param) {
  OGLTextureExtension::glTexParameterIivEXT(target, pname, (const s32_t *)&param);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
