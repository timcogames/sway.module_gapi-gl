#include <sway/gapi/gl/oglrenderbuffer.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

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

void OGLRenderBuffer::store(PixelFormat fmt, const math::size2i_t &size, i32_t samples) {
  // bind();

  if (samples == 0) {
    helper_.setRenderBufferStorage(GL_RENDERBUFFER_EXT, fmt, size);
  } else {
    helper_.setRenderBufferStorageMultisample(GL_RENDERBUFFER_EXT, samples, fmt, size);
  }

  // unbind();
}

void OGLRenderBuffer::generate() { setUid(helper_.generateRenderBuffers(1)[GLOB_IDX_INITIAL]); }

void OGLRenderBuffer::destroy() {
  if (!helper_.isRenderBuffer(getUid())) {
    return;
  }

  auto uid = getUid().value();
  helper_.deleteRenderBuffers(1, &uid);
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
