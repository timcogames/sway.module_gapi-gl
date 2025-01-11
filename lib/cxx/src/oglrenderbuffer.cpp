#include <sway/gapi/gl/oglrenderbuffer.hpp>

namespace sway::gapi {

auto OGLRenderBuffer::createInstance() -> typedefs::RenderBufferPtr_t {
  auto instance = new OGLRenderBuffer();
  return instance;
}

OGLRenderBuffer::OGLRenderBuffer() {
  glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderBufferSize_);
  generate();
}

OGLRenderBuffer::~OGLRenderBuffer() { destroy(); }

void OGLRenderBuffer::bind() { helper_.bindRenderBuffer(GL_RENDERBUFFER_EXT, getUniqueId()); }

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

void OGLRenderBuffer::generate() { setUniqueId(helper_.generateRenderBuffers(1)[GLOB_IDX_INITIAL]); }

void OGLRenderBuffer::destroy() {
  if (!helper_.isRenderBuffer(getUniqueId())) {
    return;
  }

  auto uid = getUniqueId().value();
  helper_.deleteRenderBuffers(1, &uid);
}

}  // namespace sway::gapi
