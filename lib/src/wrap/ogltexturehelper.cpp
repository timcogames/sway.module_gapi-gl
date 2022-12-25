#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/ogltextureextension.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLTextureHelper::OGLTextureHelper() {
#ifdef _STUB
  TextureImage2D_ = &OGLTextureHelper::EMU_TextureImage2D;
  setActiveTexture_ = &OGLTextureHelper::EMU_setActiveTexture;
#else

  const auto *extensions = OGLCapability::getExtensions();
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

#endif
}

auto OGLTextureHelper::EMU_TextureImage2D([[maybe_unused]] s32_t target, [[maybe_unused]] s32_t level,
    [[maybe_unused]] s32_t internalFormat, [[maybe_unused]] s32_t width, [[maybe_unused]] s32_t height,
    [[maybe_unused]] s32_t border, [[maybe_unused]] s32_t format, [[maybe_unused]] s32_t type,
    [[maybe_unused]] const void *pixels) -> void {}

auto OGLTextureHelper::STD_TextureImage2D(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height,
    s32_t border, s32_t format, s32_t type, const void *pixels) -> void {
  glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
}

auto OGLTextureHelper::EXT_TextureImage2D(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height,
    s32_t border, s32_t format, s32_t type, const void *pixels) -> void {
  OGLTextureExtension::glTextureImage2DEXT(target, level, internalFormat, width, height, border, format, type, pixels);
}

auto OGLTextureHelper::EMU_setActiveTexture([[maybe_unused]] s32_t target) -> void {}

auto OGLTextureHelper::STD_setActiveTexture(s32_t target) -> void { glActiveTexture(target); }

auto OGLTextureHelper::ARB_setActiveTexture(s32_t target) -> void { OGLTextureExtension::glActiveTextureARB(target); }

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
