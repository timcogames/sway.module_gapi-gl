#ifndef SWAY_GAPI_GL_OGLFRAMEBUFFER_HPP
#define SWAY_GAPI_GL_OGLFRAMEBUFFER_HPP

#include <sway/gapi/framebuffer.hpp>
#include <sway/gapi/framebufferattachments.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglframebufferhelper.hpp>
#include <sway/gapi/idgenerator.hpp>
#include <sway/gapi/renderbuffer.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLFrameBuffer : public FrameBuffer {
public:
#pragma region "Static methods"

  static auto attachmentToGLenum(FrameBufferAttachment::Enum attachment) -> u32_t;

  /**
   * @name creators
   * @{
   */

  static auto createInstance(IdGeneratorPtr_t idgen) -> FrameBufferPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  OGLFrameBuffer(IdGeneratorPtr_t idgen);

  DTOR_VIRTUAL(OGLFrameBuffer);

#pragma endregion

  void destroy();

#pragma region "Overridden FrameBuffer methods"

  MTHD_OVERRIDE(void attach(FrameBufferAttachment::Enum attachment, TexturePtr_t tex, i32_t mipLevels));

  MTHD_OVERRIDE(void attach(FrameBufferAttachment::Enum attachment, RenderBufferPtr_t buf));

  MTHD_OVERRIDE(void bind());

  MTHD_OVERRIDE(void unbind());

  MTHD_OVERRIDE(void drawBuffers(i32_t num, const u32_t *bufs));

#pragma endregion

private:
  OGLFrameBufferHelper helper_;
  i32_t maxColorAttachments_;
  // bool fboSupported_;
  // bool fboUsed_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLFRAMEBUFFER_HPP
