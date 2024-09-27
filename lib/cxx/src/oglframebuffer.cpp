#include <sway/gapi/gl/oglframebuffer.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLFramebuffer::createInstance() -> FramebufferPtr_t {
  auto instance = new OGLFramebuffer();
  return instance;
}

auto OGLFramebuffer::attachmentToGLenum(FramebufferAttachment attachment) -> u32_t {
  switch (attachment) {
    case FramebufferAttachment::DEPTH_STENCIL:
      return GL_DEPTH_STENCIL_ATTACHMENT;
    case FramebufferAttachment::DEPTH:
      return GL_DEPTH_ATTACHMENT;
    case FramebufferAttachment::STENCIL:
      return GL_STENCIL_ATTACHMENT;
    case FramebufferAttachment::COL_1:
      return GL_COLOR_ATTACHMENT0;
    case FramebufferAttachment::COL_2:
      return GL_COLOR_ATTACHMENT1;
    case FramebufferAttachment::COL_3:
      return GL_COLOR_ATTACHMENT2;
    case FramebufferAttachment::COL_4:
      return GL_COLOR_ATTACHMENT3;
    case FramebufferAttachment::COL_5:
      return GL_COLOR_ATTACHMENT4;
    default:
      return GL_COLOR_ATTACHMENT0;
  }
}

OGLFramebuffer::OGLFramebuffer() {
  glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxColorAttachments_);

  u32_t objname;
  helper_.generateFramebuffers(1, &objname);
  setUid(objname);
}

OGLFramebuffer::~OGLFramebuffer() { destroy(); }

void OGLFramebuffer::destroy() {
  auto uid = getUid().value();
  if (!helper_.isFramebuffer(uid)) {
    return;
  }

  helper_.deleteFramebuffers(1, &uid);
}

void OGLFramebuffer::bind() { helper_.bindFramebuffer(GL_FRAMEBUFFER_EXT, getUid()); }

void OGLFramebuffer::unbind() { helper_.bindFramebuffer(GL_FRAMEBUFFER_EXT, 0); }

void OGLFramebuffer::attach(FramebufferAttachment attachment, TexturePtr_t tex, i32_t mipLevels) {
  bind();
  helper_.framebufferTexture2D(
      GL_FRAMEBUFFER_EXT, OGLFramebuffer::attachmentToGLenum(attachment), GL_TEXTURE_2D, tex->getUid(), mipLevels);
  unbind();
}

void OGLFramebuffer::attach(FramebufferAttachment attachment, RenderBufferPtr_t buf) {
  bind();
  helper_.framebufferRenderbuffer(
      GL_FRAMEBUFFER_EXT, OGLFramebuffer::attachmentToGLenum(attachment), GL_RENDERBUFFER_EXT, buf->getUid());
  unbind();
}

void OGLFramebuffer::drawBuffers(i32_t num, const u32_t *bufs) { glDrawBuffers(num, bufs); }

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
