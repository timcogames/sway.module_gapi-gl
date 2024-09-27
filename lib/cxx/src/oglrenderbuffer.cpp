#include <sway/gapi/gl/oglrenderbuffer.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLRenderBuffer::createInstance() -> RenderBufferPtr_t {
  auto instance = new OGLRenderBuffer();
  return instance;
}

OGLRenderBuffer::OGLRenderBuffer() {
  glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderBufferSize_);
  generate();
}

OGLRenderBuffer::~OGLRenderBuffer() { destroy(); }

void OGLRenderBuffer::bind() { helper_.bindRenderBuffer(GL_RENDERBUFFER_EXT, getUid()); }

void OGLRenderBuffer::unbind() { helper_.bindRenderBuffer(GL_RENDERBUFFER_EXT, 0); }

void OGLRenderBuffer::store(const math::size2i_t &size) {
  bind();
  helper_.setRenderBufferStorage(GL_RENDERBUFFER_EXT, GL_DEPTH24_STENCIL8, size);
  unbind();
}

void OGLRenderBuffer::generate() { setUid(helper_.generateRenderBuffers(1)[GLOB_IDX_INITIAL]); }

void OGLRenderBuffer::destroy() {
  if (!helper_.isRenderBuffer(getUid())) {
    return;
  }

  auto uid = getUid().value();
  helper_.deleteRenderBuffers(1, &uid);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
