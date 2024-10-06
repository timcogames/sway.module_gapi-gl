#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/oglpixelformatconvertor.hpp>
#include <sway/gapi/gl/ogltexturetargetconvertor.hpp>
#include <sway/gapi/gl/wrap/ogltextureextension.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

OGLTextureHelper::OGLTextureHelper() {
#ifdef _STUB
  generateTextures_ = &OGLTextureHelper::EMU_GenerateTextures;
  deleteTextures_ = &OGLTextureHelper::EMU_DeleteTextures;
  bindTexture_ = &OGLTextureHelper::EMU_BindTexture;
  textureImage2D_ = &OGLTextureHelper::EMU_TextureImage2D;
  texSubImage2D_ = &OGLTextureHelper::EMU_TexSubImage2D;
  setActiveTexture_ = &OGLTextureHelper::EMU_SetActiveTexture;
  setTextureParamI_ = &OGLTextureHelper::EMU_SetTextureParamI;
#else

  const auto *extensions = OGLCapability::getExtensions();

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_texture_object")) {
    generateTextures_ = &OGLTextureHelper::EXT_GenerateTextures;
    deleteTextures_ = &OGLTextureHelper::EXT_DeleteTextures;
    bindTexture_ = &OGLTextureHelper::EXT_BindTexture;
  } else {
    generateTextures_ = &OGLTextureHelper::STD_GenerateTextures;
    deleteTextures_ = &OGLTextureHelper::STD_DeleteTextures;
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

void OGLTextureHelper::EMU_GenerateTextures(
    [[maybe_unused]] u32_t latest, [[maybe_unused]] i32_t num, [[maybe_unused]] ObjectUid_t *uids) {
  for (auto i = 0; i < num; ++i) {
    uids[i] = i + latest + 1;
  }
}

void OGLTextureHelper::STD_GenerateTextures(u32_t latest, i32_t num, ObjectUid_t *uids) { glGenTextures(num, uids); }

void OGLTextureHelper::EXT_GenerateTextures(u32_t latest, i32_t num, ObjectUid_t *uids) {
  OGLTextureExtension::glGenTexturesEXT(num, uids);
}

void OGLTextureHelper::EMU_DeleteTextures([[maybe_unused]] i32_t num, [[maybe_unused]] ObjectUid_t *uids) {}

void OGLTextureHelper::STD_DeleteTextures(i32_t num, ObjectUid_t *uids) { glDeleteTextures(num, uids); }

void OGLTextureHelper::EXT_DeleteTextures(i32_t num, ObjectUid_t *uids) {
  OGLTextureExtension::glDeleteTexturesEXT(num, uids);
}

void OGLTextureHelper::EMU_BindTexture(
    [[maybe_unused]] TextureTarget::Enum target, [[maybe_unused]] ObjectUidOpt_t uid) {}

void OGLTextureHelper::STD_BindTexture(TextureTarget::Enum target, ObjectUidOpt_t uid) {
  glBindTexture(OGLTextureTargetConvertor::toGLenum(target), uid.value());
}

void OGLTextureHelper::EXT_BindTexture(TextureTarget::Enum target, ObjectUidOpt_t uid) {
  OGLTextureExtension::glBindTextureEXT(OGLTextureTargetConvertor::toGLenum(target), uid.value());
}

void OGLTextureHelper::EMU_TextureImage2D([[maybe_unused]] TextureTarget::Enum target, [[maybe_unused]] i32_t level,
    [[maybe_unused]] PixelFormat internalFormat, [[maybe_unused]] math::size2i_t size, [[maybe_unused]] i32_t border,
    [[maybe_unused]] PixelFormat frm, [[maybe_unused]] core::ValueDataType::Enum type,
    [[maybe_unused]] const void *pixels) {}

void OGLTextureHelper::STD_TextureImage2D(TextureTarget::Enum target, i32_t level, PixelFormat internalFormat,
    math::size2i_t size, i32_t border, PixelFormat frm, core::ValueDataType::Enum type, const void *pixels) {
  if (target != TextureTarget::Enum::TEX_2D) {
    return;
  }

  glTexImage2D(OGLTextureTargetConvertor::toGLenum(target), level, OGLPixelFormatConvertor::toGLenum(internalFormat),
      size.getW(), size.getH(), border, OGLPixelFormatConvertor::toGLenum(frm), TypeUtils::toGL(type), pixels);
}

void OGLTextureHelper::EXT_TextureImage2D(TextureTarget::Enum target, i32_t level, PixelFormat internalFormat,
    math::size2i_t size, i32_t border, PixelFormat frm, core::ValueDataType::Enum type, const void *pixels) {
  if (target != TextureTarget::Enum::TEX_2D) {
    return;
  }

  OGLTextureExtension::glTextureImage2DEXT(OGLTextureTargetConvertor::toGLenum(target), level,
      OGLPixelFormatConvertor::toGLenum(internalFormat), size.getW(), size.getH(), border,
      OGLPixelFormatConvertor::toGLenum(frm), TypeUtils::toGL(type), pixels);
}

void OGLTextureHelper::EMU_TexSubImage2D([[maybe_unused]] TextureTarget::Enum target, [[maybe_unused]] i32_t level,
    [[maybe_unused]] i32_t xoffset, [[maybe_unused]] i32_t yoffset, [[maybe_unused]] i32_t wdt,
    [[maybe_unused]] i32_t hgt, [[maybe_unused]] PixelFormat frm, [[maybe_unused]] core::ValueDataType::Enum type,
    [[maybe_unused]] const void *pixels) {}

void OGLTextureHelper::STD_TexSubImage2D(TextureTarget::Enum target, i32_t level, i32_t xoffset, i32_t yoffset,
    i32_t wdt, i32_t hgt, PixelFormat frm, core::ValueDataType::Enum type, const void *pixels) {
  glTexSubImage2D(OGLTextureTargetConvertor::toGLenum(target), level, xoffset, yoffset, wdt, hgt,
      OGLPixelFormatConvertor::toGLenum(frm), TypeUtils::toGL(type), pixels);
}

void OGLTextureHelper::EXT_TexSubImage2D(TextureTarget::Enum target, i32_t level, i32_t xoffset, i32_t yoffset,
    i32_t wdt, i32_t hgt, PixelFormat frm, core::ValueDataType::Enum type, const void *pixels) {
  OGLTextureExtension::glTexSubImage2DEXT(OGLTextureTargetConvertor::toGLenum(target), level, xoffset, yoffset, wdt,
      hgt, OGLPixelFormatConvertor::toGLenum(frm), TypeUtils::toGL(type), pixels);
}

void OGLTextureHelper::EMU_SetActiveTexture([[maybe_unused]] i32_t slot) {}

void OGLTextureHelper::STD_SetActiveTexture(i32_t slot) { glActiveTexture(slot); }

void OGLTextureHelper::ARB_SetActiveTexture(i32_t slot) { OGLTextureExtension::glActiveTextureARB(slot); }

void OGLTextureHelper::EMU_SetTextureParamI(
    [[maybe_unused]] TextureTarget::Enum target, [[maybe_unused]] u32_t pname, [[maybe_unused]] i32_t param) {}

void OGLTextureHelper::STD_SetTextureParamI(TextureTarget::Enum target, u32_t pname, i32_t param) {
  glTexParameteri(OGLTextureTargetConvertor::toGLenum(target), pname, param);
}

void OGLTextureHelper::EXT_SetTextureParamI(TextureTarget::Enum target, u32_t pname, i32_t param) {
  OGLTextureExtension::glTexParameterIivEXT(OGLTextureTargetConvertor::toGLenum(target), pname, (const i32_t *)&param);
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
