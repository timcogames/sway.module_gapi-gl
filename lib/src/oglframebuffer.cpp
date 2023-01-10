#include <sway/gapi/gl/oglframebuffer.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLFramebuffer::createInstance() -> std::shared_ptr<Framebuffer> {
  auto instance = std::make_shared<OGLFramebuffer>();
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

OGLFramebuffer::~OGLFramebuffer() {
  auto objname = getUid().value();

  if (helper_.isFramebuffer(objname)) {
    helper_.deleteFramebuffers(1, &objname);
  }
}

void OGLFramebuffer::attach(FramebufferAttachment attachment, TextureRef_t texture, int mipLevels) {
  helper_.bindFramebuffer(GL_FRAMEBUFFER_EXT, getUid());
  helper_.framebufferTexture2D(
      GL_FRAMEBUFFER_EXT, OGLFramebuffer::attachmentToGLenum(attachment), GL_TEXTURE_2D, texture->getUid(), mipLevels);
  helper_.bindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
}

void OGLFramebuffer::attach(FramebufferAttachment attachment, std::shared_ptr<Renderbuffer> renderbuffer) {
  helper_.bindFramebuffer(GL_FRAMEBUFFER_EXT, getUid());
  helper_.framebufferRenderbuffer(
      GL_FRAMEBUFFER_EXT, OGLFramebuffer::attachmentToGLenum(attachment), GL_RENDERBUFFER_EXT, renderbuffer->getUid());
  helper_.bindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
}

void OGLFramebuffer::bind() { helper_.bindFramebuffer(GL_FRAMEBUFFER_EXT, getUid()); }

void OGLFramebuffer::unbind() { helper_.bindFramebuffer(GL_FRAMEBUFFER_EXT, 0); }

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
