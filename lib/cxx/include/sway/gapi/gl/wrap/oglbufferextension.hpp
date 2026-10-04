#ifndef SWAY_GAPI_GL_WRAP_OGLBUFFEREXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLBUFFEREXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

class OGLBufferExtension {
public:
  static core::TFunctionPointer<void(i32_t, u32_t *)> glGenBuffersARB;
  static core::TFunctionPointer<void(i32_t, const u32_t *)> glDeleteBuffersARB;
  static core::TFunctionPointer<void(u32_t, u32_t)> glBindBufferARB;
  static core::TFunctionPointer<void(u32_t, u32_t, u32_t, ptrdiff_t, ptrdiff_t)> glBindBufferRangeEXT;
  static core::TFunctionPointer<void(u32_t, ptrdiff_t, const void *, u32_t)> glBufferDataARB;
  static core::TFunctionPointer<void(u32_t, ptrdiff_t, ptrdiff_t, const void *)> glBufferSubDataARB;
  static core::TFunctionPointer<void *(u32_t, i32_t, i32_t, u32_t)> glMapBufferRangeEXT;
  static core::TFunctionPointer<void *(u32_t, u32_t)> glMapBufferARB;
  static core::TFunctionPointer<void *(u32_t, u32_t)> glMapBufferOES;
  static core::TFunctionPointer<u8_t(u32_t)> glUnmapBufferARB;
  static core::TFunctionPointer<u8_t(u32_t)> glUnmapBufferOES;
  static core::TFunctionPointer<u8_t(u32_t)> glIsBufferARB;
  static core::TFunctionPointer<void(u32_t, u32_t, i32_t *)> glGetBufferParameterivARB;

  static void define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &);
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_OGLBUFFEREXTENSION_HPP
