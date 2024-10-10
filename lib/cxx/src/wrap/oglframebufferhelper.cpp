#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglframebufferextension.hpp>
#include <sway/gapi/gl/wrap/oglframebufferhelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

OGLFrameBufferHelper::OGLFrameBufferHelper() {
#ifdef _STUB
  generateFramebuffers_ = &OGLFrameBufferHelper::EMU_GenerateFramebuffers;
  deleteFramebuffers_ = &OGLFrameBufferHelper::EMU_DeleteFramebuffers;
  bindFramebuffer_ = &OGLFrameBufferHelper::EMU_BindFramebuffer;
  isFramebuffer_ = &OGLFrameBufferHelper::EMU_IsFramebuffer;
  framebufferTexture2D_ = &OGLFrameBufferHelper::EMU_FramebufferTexture2D;
  framebufferRenderbuffer_ = &OGLFrameBufferHelper::EMU_FramebufferRenderbuffer;
  checkFramebufferStatus_ = &OGLFrameBufferHelper::EMU_CheckFramebufferStatus;
  getFramebufferAttachmentParamI_ = &OGLFrameBufferHelper::EMU_GetFramebufferAttachmentParamI;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_direct_state_access")) {
    generateFramebuffers_ = &OGLFrameBufferHelper::EXT_GenerateFramebuffers;
    deleteFramebuffers_ = &OGLFrameBufferHelper::EXT_DeleteFramebuffers;
    bindFramebuffer_ = &OGLFrameBufferHelper::EXT_BindFramebuffer;
    isFramebuffer_ = &OGLFrameBufferHelper::EXT_IsFramebuffer;
    framebufferTexture2D_ = &OGLFrameBufferHelper::EXT_FramebufferTexture2D;
    framebufferRenderbuffer_ = &OGLFrameBufferHelper::EXT_FramebufferRenderbuffer;
    checkFramebufferStatus_ = &OGLFrameBufferHelper::EXT_CheckFramebufferStatus;
    getFramebufferAttachmentParamI_ = &OGLFrameBufferHelper::EXT_GetFramebufferAttachmentParamI;
  } else {
    generateFramebuffers_ = &OGLFrameBufferHelper::STD_GenerateFramebuffers;
    deleteFramebuffers_ = &OGLFrameBufferHelper::STD_DeleteFramebuffers;
    bindFramebuffer_ = &OGLFrameBufferHelper::STD_BindFramebuffer;
    isFramebuffer_ = &OGLFrameBufferHelper::STD_IsFramebuffer;
    framebufferTexture2D_ = &OGLFrameBufferHelper::STD_FramebufferTexture2D;
    framebufferRenderbuffer_ = &OGLFrameBufferHelper::STD_FramebufferRenderbuffer;
    checkFramebufferStatus_ = &OGLFrameBufferHelper::STD_CheckFramebufferStatus;
    getFramebufferAttachmentParamI_ = &OGLFrameBufferHelper::STD_GetFramebufferAttachmentParamI;
  }

#endif
}

void OGLFrameBufferHelper::EMU_GenerateFramebuffers(u32_t latest, i32_t num, u32_t *uids) {
  for (auto i = 0; i < (i32_t)num; ++i) {
    uids[i] = i + latest + 1;
  }
}

void OGLFrameBufferHelper::STD_GenerateFramebuffers([[maybe_unused]] u32_t latest, i32_t num, u32_t *uids) {
  glGenFramebuffers(num, uids);
}

void OGLFrameBufferHelper::EXT_GenerateFramebuffers([[maybe_unused]] u32_t latest, i32_t num, u32_t *uids) {
  OGLFramebufferExtension::glGenFramebuffersEXT(num, uids);
}

void OGLFrameBufferHelper::EMU_DeleteFramebuffers(
    [[maybe_unused]] i32_t num, [[maybe_unused]] const u32_t *framebuffers) {}

void OGLFrameBufferHelper::STD_DeleteFramebuffers(i32_t num, const u32_t *framebuffers) {
  glDeleteFramebuffers(num, framebuffers);
}

void OGLFrameBufferHelper::EXT_DeleteFramebuffers(i32_t num, const u32_t *framebuffers) {
  OGLFramebufferExtension::glDeleteFramebuffersEXT(num, framebuffers);
}

void OGLFrameBufferHelper::EMU_BindFramebuffer(
    [[maybe_unused]] u32_t target, [[maybe_unused]] std::optional<u32_t> framebuffer) {}

void OGLFrameBufferHelper::STD_BindFramebuffer(u32_t target, std::optional<u32_t> framebuffer) {
  glBindFramebuffer(target, framebuffer.value());
}

void OGLFrameBufferHelper::EXT_BindFramebuffer(u32_t target, std::optional<u32_t> framebuffer) {
  OGLFramebufferExtension::glBindFramebufferEXT(target, framebuffer.value());
}

auto OGLFrameBufferHelper::EMU_IsFramebuffer([[maybe_unused]] u32_t framebuffer) -> bool { return true; }

auto OGLFrameBufferHelper::STD_IsFramebuffer(u32_t framebuffer) -> bool { return glIsFramebuffer(framebuffer); }

auto OGLFrameBufferHelper::EXT_IsFramebuffer(u32_t framebuffer) -> bool {
  return OGLFramebufferExtension::glIsFramebufferEXT(framebuffer);
}

void OGLFrameBufferHelper::EMU_FramebufferTexture2D([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t attachment,
    [[maybe_unused]] u32_t textarget, [[maybe_unused]] std::optional<u32_t> texture, [[maybe_unused]] i32_t level) {}

void OGLFrameBufferHelper::STD_FramebufferTexture2D(
    u32_t target, u32_t attachment, u32_t textarget, std::optional<u32_t> texture, i32_t level) {
  glFramebufferTexture2D(target, attachment, textarget, texture.value(), level);
}

void OGLFrameBufferHelper::EXT_FramebufferTexture2D(
    u32_t target, u32_t attachment, u32_t textarget, std::optional<u32_t> texture, i32_t level) {
  OGLFramebufferExtension::glFramebufferTexture2DEXT(target, attachment, textarget, texture.value(), level);
}

void OGLFrameBufferHelper::EMU_FramebufferRenderbuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t attachment,
    [[maybe_unused]] u32_t renderbuffertarget, [[maybe_unused]] std::optional<u32_t> renderbuffer) {}

void OGLFrameBufferHelper::STD_FramebufferRenderbuffer(
    u32_t target, u32_t attachment, u32_t renderbuffertarget, std::optional<u32_t> renderbuffer) {
  glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer.value());
}

void OGLFrameBufferHelper::EXT_FramebufferRenderbuffer(
    u32_t target, u32_t attachment, u32_t renderbuffertarget, std::optional<u32_t> renderbuffer) {
  OGLFramebufferExtension::glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer.value());
}

auto OGLFrameBufferHelper::EMU_CheckFramebufferStatus([[maybe_unused]] u32_t target) -> u32_t { return 0; }

auto OGLFrameBufferHelper::STD_CheckFramebufferStatus(u32_t target) -> u32_t {
  return glCheckFramebufferStatus(target);
}

auto OGLFrameBufferHelper::EXT_CheckFramebufferStatus(u32_t target) -> u32_t {
  return OGLFramebufferExtension::glCheckFramebufferStatusEXT(target);
}

void OGLFrameBufferHelper::EMU_GetFramebufferAttachmentParamI([[maybe_unused]] u32_t target,
    [[maybe_unused]] u32_t attachment, [[maybe_unused]] u32_t pname, [[maybe_unused]] i32_t *params) {}

void OGLFrameBufferHelper::STD_GetFramebufferAttachmentParamI(
    u32_t target, u32_t attachment, u32_t pname, i32_t *params) {
  glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

void OGLFrameBufferHelper::EXT_GetFramebufferAttachmentParamI(
    u32_t target, u32_t attachment, u32_t pname, i32_t *params) {
  OGLFramebufferExtension::glGetFramebufferAttachmentParameterivEXT(target, attachment, pname, params);
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
