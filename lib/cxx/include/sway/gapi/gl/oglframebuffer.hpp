#ifndef SWAY_GAPI_GL_OGLFRAMEBUFFER_HPP
#define SWAY_GAPI_GL_OGLFRAMEBUFFER_HPP

#include <sway/gapi/framebuffer.hpp>
#include <sway/gapi/framebufferattachments.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglframebufferhelper.hpp>
#include <sway/gapi/renderbuffer.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLFramebuffer : public Framebuffer {
public:
  static auto attachmentToGLenum(FramebufferAttachment attachment) -> u32_t;

  static auto createInstance() -> FramebufferPtr_t;

  OGLFramebuffer();

  virtual ~OGLFramebuffer();

  MTHD_OVERRIDE(void attach(FramebufferAttachment attachment, TexturePtr_t texture, int mipLevels));

  MTHD_OVERRIDE(void attach(FramebufferAttachment attachment, RenderbufferPtr_t renderbuffer));

  MTHD_OVERRIDE(void bind());

  MTHD_OVERRIDE(void unbind());

private:
  OGLFramebufferHelper helper_;
  s32_t maxColorAttachments_;
  // bool fboSupported_;
  // bool fboUsed_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLFRAMEBUFFER_HPP
