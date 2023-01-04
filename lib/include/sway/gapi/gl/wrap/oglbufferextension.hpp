#ifndef SWAY_GAPI_GL_WRAP_OGLBUFFEREXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLBUFFEREXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLBufferExtension {
public:
  static core::binding::TFunction<void(s32_t, u32_t *)> glGenBuffersARB;
  static core::binding::TFunction<void(s32_t, const u32_t *)> glDeleteBuffersARB;
  static core::binding::TFunction<void(u32_t, u32_t)> glBindBufferARB;
  static core::binding::TFunction<void(u32_t, ptrdiff_t, const void *, u32_t)> glBufferDataARB;
  static core::binding::TFunction<void(u32_t, ptrdiff_t, ptrdiff_t, const void *)> glBufferSubDataARB;
  static core::binding::TFunction<u8_t(u32_t)> glIsBufferARB;
  static core::binding::TFunction<void(u32_t, u32_t, s32_t *)> glGetBufferParameterivARB;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLBUFFEREXTENSION_HPP
