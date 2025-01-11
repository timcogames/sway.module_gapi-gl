#ifndef SWAY_GAPI_GL_WRAP_OGLBUFFEREXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLBUFFEREXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

class OGLBufferExtension {
public:
  static core::TFunction<void(i32_t, u32_t *)> glGenBuffersARB;
  static core::TFunction<void(i32_t, const u32_t *)> glDeleteBuffersARB;
  static core::TFunction<void(u32_t, u32_t)> glBindBufferARB;
  static core::TFunction<void(u32_t, u32_t, u32_t, ptrdiff_t, ptrdiff_t)> glBindBufferRangeEXT;
  static core::TFunction<void(u32_t, ptrdiff_t, const void *, u32_t)> glBufferDataARB;
  static core::TFunction<void(u32_t, ptrdiff_t, ptrdiff_t, const void *)> glBufferSubDataARB;
  static core::TFunction<void *(u32_t, i32_t, i32_t, u32_t)> glMapBufferRangeEXT;
  static core::TFunction<void *(u32_t, u32_t)> glMapBufferARB;
  static core::TFunction<void *(u32_t, u32_t)> glMapBufferOES;
  static core::TFunction<u8_t(u32_t)> glUnmapBufferARB;
  static core::TFunction<u8_t(u32_t)> glUnmapBufferOES;
  static core::TFunction<u8_t(u32_t)> glIsBufferARB;
  static core::TFunction<void(u32_t, u32_t, i32_t *)> glGetBufferParameterivARB;

  static void define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &);
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_OGLBUFFEREXTENSION_HPP
