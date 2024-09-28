#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/oglpixelformatconvertor.hpp>
#include <sway/gapi/gl/wrap/oglrenderbufferextension.hpp>
#include <sway/gapi/gl/wrap/oglrenderbufferhelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLRenderBufferHelper::OGLRenderBufferHelper() {
#ifdef _STUB
  generateRenderBuffers_ = &OGLRenderBufferHelper::EMU_GenerateRenderBuffers;
  deleteRenderBuffers_ = &OGLRenderBufferHelper::EMU_DeleteRenderBuffers;
  bindRenderBuffer_ = &OGLRenderBufferHelper::EMU_BindRenderBuffer;
  isRenderBuffer_ = &OGLRenderBufferHelper::EMU_IsRenderBuffer;
  setRenderBufferStorage_ = &OGLRenderBufferHelper::EMU_SetRenderBufferStorage;
  setRenderBufferStorageMultisample_ = &OGLRenderBufferHelper::EMU_SetRenderBufferStorageMultisample;
  blitFrameBuffer_ = &OGLRenderBufferHelper::EMU_BlitFrameBuffer;
  getRenderBufferParameter_ = &OGLRenderBufferHelper::EMU_GetRenderBufferParameter;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_direct_state_access")) {
    generateRenderBuffers_ = &OGLRenderBufferHelper::EXT_GenerateRenderBuffers;
    deleteRenderBuffers_ = &OGLRenderBufferHelper::EXT_DeleteRenderBuffers;
    bindRenderBuffer_ = &OGLRenderBufferHelper::EXT_BindRenderBuffer;
    isRenderBuffer_ = &OGLRenderBufferHelper::EXT_IsRenderBuffer;
    setRenderBufferStorage_ = &OGLRenderBufferHelper::EXT_SetRenderBufferStorage;
    setRenderBufferStorageMultisample_ = &OGLRenderBufferHelper::EXT_SetRenderBufferStorageMultisample;
    blitFrameBuffer_ = &OGLRenderBufferHelper::EXT_BlitFrameBuffer;
    getRenderBufferParameter_ = &OGLRenderBufferHelper::EXT_GetRenderBufferParameter;
  } else {
    generateRenderBuffers_ = &OGLRenderBufferHelper::STD_GenerateRenderBuffers;
    deleteRenderBuffers_ = &OGLRenderBufferHelper::STD_DeleteRenderBuffers;
    bindRenderBuffer_ = &OGLRenderBufferHelper::STD_BindRenderBuffer;
    isRenderBuffer_ = &OGLRenderBufferHelper::STD_IsRenderBuffer;
    setRenderBufferStorage_ = &OGLRenderBufferHelper::STD_SetRenderBufferStorage;
    setRenderBufferStorageMultisample_ = &OGLRenderBufferHelper::STD_SetRenderBufferStorageMultisample;
    blitFrameBuffer_ = &OGLRenderBufferHelper::STD_BlitFrameBuffer;
    getRenderBufferParameter_ = &OGLRenderBufferHelper::STD_GetRenderBufferParameter;
  }

#endif
}

auto OGLRenderBufferHelper::EMU_GenerateRenderBuffers([[maybe_unused]] i32_t num) -> std::vector<u32_t> { return {}; }

auto OGLRenderBufferHelper::STD_GenerateRenderBuffers([[maybe_unused]] i32_t num) -> std::vector<u32_t> {
  auto *bufs = new u32_t[num];
  glGenRenderbuffers(num, bufs);

  std::vector<u32_t> out;
  for (auto i = 0; i < num; ++i) {
    out.push_back(bufs[i]);
  }

  SAFE_DELETE_ARRAY(bufs);
  return out;
}

auto OGLRenderBufferHelper::EXT_GenerateRenderBuffers(i32_t num) -> std::vector<u32_t> {
  auto *bufs = new u32_t[num];
  OGLRenderBufferExtension::glGenRenderbuffersEXT(num, bufs);

  std::vector<u32_t> out;
  for (auto i = 0; i < num; ++i) {
    out.push_back(bufs[i]);
  }

  SAFE_DELETE_ARRAY(bufs);
  return out;
}

void OGLRenderBufferHelper::EMU_DeleteRenderBuffers([[maybe_unused]] i32_t num, [[maybe_unused]] const u32_t *bufs) {}

void OGLRenderBufferHelper::STD_DeleteRenderBuffers(i32_t num, const u32_t *bufs) { glDeleteRenderbuffers(num, bufs); }

void OGLRenderBufferHelper::EXT_DeleteRenderBuffers(i32_t num, const u32_t *bufs) {
  OGLRenderBufferExtension::glDeleteRenderbuffersEXT(num, bufs);
}

void OGLRenderBufferHelper::EMU_BindRenderBuffer(
    [[maybe_unused]] u32_t target, [[maybe_unused]] std::optional<u32_t> buf) {}

void OGLRenderBufferHelper::STD_BindRenderBuffer(u32_t target, std::optional<u32_t> buf) {
  glBindRenderbuffer(target, buf.value());
}

void OGLRenderBufferHelper::EXT_BindRenderBuffer(u32_t target, std::optional<u32_t> buf) {
  OGLRenderBufferExtension::glBindRenderbufferEXT(target, buf.value());
}

auto OGLRenderBufferHelper::EMU_IsRenderBuffer([[maybe_unused]] std::optional<u32_t> buf) -> bool { return true; }

auto OGLRenderBufferHelper::STD_IsRenderBuffer(std::optional<u32_t> buf) -> bool {
  return glIsRenderbuffer(buf.value());
}

auto OGLRenderBufferHelper::EXT_IsRenderBuffer(std::optional<u32_t> buf) -> bool {
  return OGLRenderBufferExtension::glIsRenderbufferEXT(buf.value());
}

void OGLRenderBufferHelper::EMU_SetRenderBufferStorage(
    [[maybe_unused]] u32_t target, [[maybe_unused]] PixelFormat fmt, [[maybe_unused]] const math::size2i_t &size) {}

void OGLRenderBufferHelper::STD_SetRenderBufferStorage(
    [[maybe_unused]] u32_t target, [[maybe_unused]] PixelFormat fmt, [[maybe_unused]] const math::size2i_t &size) {
  glRenderbufferStorage(target, OGLPixelFormatConvertor::toGLenum(fmt), size.getW(), size.getH());
}

void OGLRenderBufferHelper::EXT_SetRenderBufferStorage(u32_t target, PixelFormat fmt, const math::size2i_t &size) {
  OGLRenderBufferExtension::glRenderbufferStorageEXT(
      target, OGLPixelFormatConvertor::toGLenum(fmt), size.getW(), size.getH());
}

void OGLRenderBufferHelper::EMU_SetRenderBufferStorageMultisample([[maybe_unused]] u32_t target, i32_t samples,
    [[maybe_unused]] PixelFormat fmt, [[maybe_unused]] const math::size2i_t &size) {}

void OGLRenderBufferHelper::STD_SetRenderBufferStorageMultisample([[maybe_unused]] u32_t target, i32_t samples,
    [[maybe_unused]] PixelFormat fmt, [[maybe_unused]] const math::size2i_t &size) {
  glRenderbufferStorageMultisample(target, samples, OGLPixelFormatConvertor::toGLenum(fmt), size.getW(), size.getH());
}

void OGLRenderBufferHelper::EXT_SetRenderBufferStorageMultisample(
    u32_t target, i32_t samples, PixelFormat fmt, const math::size2i_t &size) {
  OGLRenderBufferExtension::glRenderbufferStorageMultisampleEXT(
      target, samples, OGLPixelFormatConvertor::toGLenum(fmt), size.getW(), size.getH());
}

void OGLRenderBufferHelper::EMU_BlitFrameBuffer([[maybe_unused]] const math::rect4i_t &src,
    [[maybe_unused]] const math::rect4i_t &dst, [[maybe_unused]] u32_t mask, [[maybe_unused]] u32_t filter) {}

void OGLRenderBufferHelper::STD_BlitFrameBuffer(
    const math::rect4i_t &src, const math::rect4i_t &dst, u32_t mask, u32_t filter) {
  glBlitFramebuffer(
      src.getX(), src.getY(), src.getW(), src.getH(), dst.getX(), dst.getY(), dst.getW(), dst.getH(), mask, filter);
}

void OGLRenderBufferHelper::EXT_BlitFrameBuffer(
    const math::rect4i_t &src, const math::rect4i_t &dst, u32_t mask, u32_t filter) {
  OGLRenderBufferExtension::glBlitFramebufferEXT(
      src.getX(), src.getY(), src.getW(), src.getH(), dst.getX(), dst.getY(), dst.getW(), dst.getH(), mask, filter);
}

void OGLRenderBufferHelper::EMU_GetRenderBufferParameter(
    [[maybe_unused]] u32_t target, [[maybe_unused]] u32_t pname, [[maybe_unused]] i32_t *params) {}

void OGLRenderBufferHelper::STD_GetRenderBufferParameter(
    [[maybe_unused]] u32_t target, [[maybe_unused]] u32_t pname, [[maybe_unused]] i32_t *params) {
  glGetRenderbufferParameteriv(target, pname, params);
}

void OGLRenderBufferHelper::EXT_GetRenderBufferParameter(u32_t target, u32_t pname, i32_t *params) {
  OGLRenderBufferExtension::glGetRenderbufferParameterivEXT(target, pname, params);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
