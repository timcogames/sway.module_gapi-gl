#include <sway/gapi/gl/oglframebuffer.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLFrameBuffer::createInstance(IdGeneratorPtr_t idgen) -> FrameBufferPtr_t {
  auto *instance = new OGLFrameBuffer(idgen);
  return instance;
}

auto OGLFrameBuffer::attachmentToGLenum(FrameBufferAttachment::Enum attachment) -> u32_t {
  switch (attachment) {
    case FrameBufferAttachment::Enum::DEPTH_STENCIL:
      return GL_DEPTH_STENCIL_ATTACHMENT;
    case FrameBufferAttachment::Enum::DEPTH:
      return GL_DEPTH_ATTACHMENT;
    case FrameBufferAttachment::Enum::STENCIL:
      return GL_STENCIL_ATTACHMENT;
    case FrameBufferAttachment::Enum::COL_1:
      return GL_COLOR_ATTACHMENT0;
    case FrameBufferAttachment::Enum::COL_2:
      return GL_COLOR_ATTACHMENT1;
    case FrameBufferAttachment::Enum::COL_3:
      return GL_COLOR_ATTACHMENT2;
    case FrameBufferAttachment::Enum::COL_4:
      return GL_COLOR_ATTACHMENT3;
    case FrameBufferAttachment::Enum::COL_5:
      return GL_COLOR_ATTACHMENT4;
    default:
      return GL_COLOR_ATTACHMENT0;
  }
}

OGLFrameBuffer::OGLFrameBuffer(IdGeneratorPtr_t idgen) {
  glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxColorAttachments_);
  std::cout << "GL_MAX_COLOR_ATTACHMENTS: " << maxColorAttachments_ << std::endl;
  setUid(idgen->getNextUid());
}

OGLFrameBuffer::~OGLFrameBuffer() { destroy(); }

void OGLFrameBuffer::destroy() {
  // auto uid = getUid().value();
  // if (!helper_.isFramebuffer(uid)) {
  //   return;
  // }

  // helper_.deleteFramebuffers(1, &uid);
}

void OGLFrameBuffer::bind() { helper_.bindFramebuffer(GL_FRAMEBUFFER, getUid()); }

void OGLFrameBuffer::unbind() { helper_.bindFramebuffer(GL_FRAMEBUFFER, 0); }

void OGLFrameBuffer::attach(FrameBufferAttachment::Enum attachment, TexturePtr_t tex, i32_t mipLevels) {
  // bind();
  helper_.framebufferTexture2D(
      GL_FRAMEBUFFER, OGLFrameBuffer::attachmentToGLenum(attachment), GL_TEXTURE_2D, tex->getUid(), mipLevels);
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "ERROR: Failed to initialize FB" << std::endl;
  }
  // unbind();
}

void OGLFrameBuffer::attach(FrameBufferAttachment::Enum attachment, RenderBufferPtr_t buf) {
  // bind();
  helper_.framebufferRenderbuffer(
      GL_FRAMEBUFFER, OGLFrameBuffer::attachmentToGLenum(attachment), GL_RENDERBUFFER_EXT, buf->getUid());
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "ERROR: Failed to initialize FB" << std::endl;
  }
  // unbind();
}

void OGLFrameBuffer::drawBuffers(i32_t num, const u32_t *bufs) { glDrawBuffers(num, bufs); }

NS_END()  // namespace gapi
NS_END()  // namespace sway
