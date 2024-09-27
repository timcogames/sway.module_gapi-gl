#ifndef SWAY_GAPI_GL_OGLRENDERBUFFER_HPP
#define SWAY_GAPI_GL_OGLRENDERBUFFER_HPP

#include <sway/gapi/framebuffer.hpp>
#include <sway/gapi/framebufferattachments.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglrenderbufferhelper.hpp>
#include <sway/gapi/renderbuffer.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLRenderBuffer : public RenderBuffer {
public:
  static auto createInstance() -> RenderBufferPtr_t;

  OGLRenderBuffer();

  virtual ~OGLRenderBuffer();

  MTHD_OVERRIDE(void bind());

  MTHD_OVERRIDE(void unbind());

  MTHD_OVERRIDE(void store(const math::size2i_t &size));

  void generate();

  void destroy();

private:
  OGLRenderBufferHelper helper_;
  i32_t maxRenderBufferSize_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLRENDERBUFFER_HPP
