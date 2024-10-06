#ifndef SWAY_GAPI_GL_OGLFRAMEBUFFER_HPP
#define SWAY_GAPI_GL_OGLFRAMEBUFFER_HPP

#include <sway/gapi/framebuffer.hpp>
#include <sway/gapi/framebufferattachments.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglframebufferhelper.hpp>
#include <sway/gapi/renderbuffer.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLFramebuffer : public Framebuffer {
public:
  static auto attachmentToGLenum(FramebufferAttachment::Enum attachment) -> u32_t;

  static auto createInstance() -> FramebufferPtr_t;

  OGLFramebuffer();

  virtual ~OGLFramebuffer();

  void destroy();

  MTHD_OVERRIDE(void attach(FramebufferAttachment::Enum attachment, TexturePtr_t tex, i32_t mipLevels));

  MTHD_OVERRIDE(void attach(FramebufferAttachment::Enum attachment, RenderBufferPtr_t buf));

  MTHD_OVERRIDE(void bind());

  MTHD_OVERRIDE(void unbind());

  MTHD_OVERRIDE(void drawBuffers(i32_t num, const u32_t *bufs));

private:
  OGLFramebufferHelper helper_;
  i32_t maxColorAttachments_;
  // bool fboSupported_;
  // bool fboUsed_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLFRAMEBUFFER_HPP
