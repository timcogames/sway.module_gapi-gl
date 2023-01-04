#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglframebufferextension.hpp>
#include <sway/gapi/gl/wrap/oglframebufferhelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLFramebufferHelper::OGLFramebufferHelper() {
#ifdef _STUB
  generateFramebuffers_ = &OGLFramebufferHelper::EMU_GenerateFramebuffers;
  deleteFramebuffers_ = &OGLFramebufferHelper::EMU_DeleteFramebuffers;
  bindFramebuffer_ = &OGLFramebufferHelper::EMU_BindFramebuffer;
  isFramebuffer_ = &OGLFramebufferHelper::EMU_IsFramebuffer;
  framebufferTexture2D_ = &OGLFramebufferHelper::EMU_FramebufferTexture2D;
  framebufferRenderbuffer_ = &OGLFramebufferHelper::EMU_FramebufferRenderbuffer;
  checkFramebufferStatus_ = &OGLFramebufferHelper::EMU_CheckFramebufferStatus;
  getFramebufferAttachmentParamI_ = &OGLFramebufferHelper::EMU_GetFramebufferAttachmentParamI;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_direct_state_access")) {
    generateFramebuffers_ = &OGLFramebufferHelper::EXT_GenerateFramebuffers;
    deleteFramebuffers_ = &OGLFramebufferHelper::EXT_DeleteFramebuffers;
    bindFramebuffer_ = &OGLFramebufferHelper::EXT_BindFramebuffer;
    isFramebuffer_ = &OGLFramebufferHelper::EXT_IsFramebuffer;
    framebufferTexture2D_ = &OGLFramebufferHelper::EXT_FramebufferTexture2D;
    framebufferRenderbuffer_ = &OGLFramebufferHelper::EXT_FramebufferRenderbuffer;
    checkFramebufferStatus_ = &OGLFramebufferHelper::EXT_CheckFramebufferStatus;
    getFramebufferAttachmentParamI_ = &OGLFramebufferHelper::EXT_GetFramebufferAttachmentParamI;
  } else {
    generateFramebuffers_ = &OGLFramebufferHelper::STD_GenerateFramebuffers;
    deleteFramebuffers_ = &OGLFramebufferHelper::STD_DeleteFramebuffers;
    bindFramebuffer_ = &OGLFramebufferHelper::STD_BindFramebuffer;
    isFramebuffer_ = &OGLFramebufferHelper::STD_IsFramebuffer;
    framebufferTexture2D_ = &OGLFramebufferHelper::STD_FramebufferTexture2D;
    framebufferRenderbuffer_ = &OGLFramebufferHelper::STD_FramebufferRenderbuffer;
    checkFramebufferStatus_ = &OGLFramebufferHelper::STD_CheckFramebufferStatus;
    getFramebufferAttachmentParamI_ = &OGLFramebufferHelper::STD_GetFramebufferAttachmentParamI;
  }

#endif
}

void OGLFramebufferHelper::EMU_GenerateFramebuffers([[maybe_unused]] s32_t num, [[maybe_unused]] u32_t *framebuffers) {}

void OGLFramebufferHelper::STD_GenerateFramebuffers(s32_t num, u32_t *framebuffers) {
  // glGenFramebuffers(num, framebuffers);
}

void OGLFramebufferHelper::EXT_GenerateFramebuffers(s32_t num, u32_t *framebuffers) {
  OGLFramebufferExtension::glGenFramebuffersEXT(num, framebuffers);
}

void OGLFramebufferHelper::EMU_DeleteFramebuffers(
    [[maybe_unused]] s32_t num, [[maybe_unused]] const u32_t *framebuffers) {}

void OGLFramebufferHelper::STD_DeleteFramebuffers(s32_t num, const u32_t *framebuffers) {
  // glDeleteFramebuffers(num, framebuffers);
}

void OGLFramebufferHelper::EXT_DeleteFramebuffers(s32_t num, const u32_t *framebuffers) {
  OGLFramebufferExtension::glDeleteFramebuffersEXT(num, framebuffers);
}

void OGLFramebufferHelper::EMU_BindFramebuffer(
    [[maybe_unused]] u32_t target, [[maybe_unused]] std::optional<u32_t> framebuffer) {}

void OGLFramebufferHelper::STD_BindFramebuffer(u32_t target, std::optional<u32_t> framebuffer) {
  // glBindFramebuffer(target, framebuffer);
}

void OGLFramebufferHelper::EXT_BindFramebuffer(u32_t target, std::optional<u32_t> framebuffer) {
  OGLFramebufferExtension::glBindFramebufferEXT(target, framebuffer.value());
}

auto OGLFramebufferHelper::EMU_IsFramebuffer([[maybe_unused]] u32_t framebuffer) -> bool { return true; }

auto OGLFramebufferHelper::STD_IsFramebuffer(u32_t framebuffer) -> bool {
  // return glIsFramebuffer(framebuffer);
  return true;
}

auto OGLFramebufferHelper::EXT_IsFramebuffer(u32_t framebuffer) -> bool {
  return OGLFramebufferExtension::glIsFramebufferEXT(framebuffer);
}

void OGLFramebufferHelper::EMU_FramebufferTexture2D([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t attachment,
    [[maybe_unused]] u32_t textarget, [[maybe_unused]] std::optional<u32_t> texture, [[maybe_unused]] s32_t level) {}

void OGLFramebufferHelper::STD_FramebufferTexture2D(
    u32_t target, u32_t attachment, u32_t textarget, std::optional<u32_t> texture, s32_t level) {
  // glFramebufferTexture2D(target, attachment, textarget, texture.value(), level);
}

void OGLFramebufferHelper::EXT_FramebufferTexture2D(
    u32_t target, u32_t attachment, u32_t textarget, std::optional<u32_t> texture, s32_t level) {
  OGLFramebufferExtension::glFramebufferTexture2DEXT(target, attachment, textarget, texture.value(), level);
}

void OGLFramebufferHelper::EMU_FramebufferRenderbuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t attachment,
    [[maybe_unused]] u32_t renderbuffertarget, [[maybe_unused]] std::optional<u32_t> renderbuffer) {}

void OGLFramebufferHelper::STD_FramebufferRenderbuffer(
    u32_t target, u32_t attachment, u32_t renderbuffertarget, std::optional<u32_t> renderbuffer) {
  // glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void OGLFramebufferHelper::EXT_FramebufferRenderbuffer(
    u32_t target, u32_t attachment, u32_t renderbuffertarget, std::optional<u32_t> renderbuffer) {
  OGLFramebufferExtension::glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer.value());
}

auto OGLFramebufferHelper::EMU_CheckFramebufferStatus([[maybe_unused]] u32_t target) -> u32_t { return 0; }

auto OGLFramebufferHelper::STD_CheckFramebufferStatus(u32_t target) -> u32_t {
  // return glCheckFramebufferStatus(target);
  return 0;
}

auto OGLFramebufferHelper::EXT_CheckFramebufferStatus(u32_t target) -> u32_t {
  return OGLFramebufferExtension::glCheckFramebufferStatusEXT(target);
}

void OGLFramebufferHelper::EMU_GetFramebufferAttachmentParamI([[maybe_unused]] u32_t target,
    [[maybe_unused]] u32_t attachment, [[maybe_unused]] u32_t pname, [[maybe_unused]] s32_t *params) {}

void OGLFramebufferHelper::STD_GetFramebufferAttachmentParamI(
    u32_t target, u32_t attachment, u32_t pname, s32_t *params) {
  // glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

void OGLFramebufferHelper::EXT_GetFramebufferAttachmentParamI(
    u32_t target, u32_t attachment, u32_t pname, s32_t *params) {
  OGLFramebufferExtension::glGetFramebufferAttachmentParameterivEXT(target, attachment, pname, params);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
