#ifndef SWAY_GAPI_GL_OGLRENDERBUFFER_HPP
#define SWAY_GAPI_GL_OGLRENDERBUFFER_HPP

#include <sway/gapi/framebuffer.hpp>
#include <sway/gapi/framebufferattachments.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglrenderbufferhelper.hpp>
#include <sway/gapi/renderbuffer.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLRenderBuffer : public RenderBuffer {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance() -> RenderBufferPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  OGLRenderBuffer();

  DTOR_VIRTUAL(OGLRenderBuffer);

#pragma endregion

#pragma region "Overridden RenderBuffer methods"

  MTHD_OVERRIDE(void bind());

  MTHD_OVERRIDE(void unbind());

  MTHD_OVERRIDE(void store(PixelFormat fmt, const math::size2i_t &size, i32_t samples));

#pragma endregion

  void generate();

  void destroy();

private:
  OGLRenderBufferHelper helper_;
  i32_t maxRenderBufferSize_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLRENDERBUFFER_HPP
