#ifndef SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFEREXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFEREXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLFramebufferExtension {
public:
  static core::binding::TFunction<void(i32_t, u32_t *)> glGenFramebuffersEXT;
  static core::binding::TFunction<void(i32_t, const u32_t *)> glDeleteFramebuffersEXT;
  static core::binding::TFunction<void(u32_t, u32_t)> glBindFramebufferEXT;
  static core::binding::TFunction<bool(u32_t)> glIsFramebufferEXT;
  static core::binding::TFunction<void(u32_t, u32_t, u32_t, u32_t, i32_t)> glFramebufferTexture2DEXT;
  static core::binding::TFunction<void(u32_t, u32_t, u32_t, u32_t)> glFramebufferRenderbufferEXT;
  static core::binding::TFunction<u32_t(u32_t)> glCheckFramebufferStatusEXT;
  static core::binding::TFunction<void(u32_t, u32_t, u32_t, i32_t *)> glGetFramebufferAttachmentParameterivEXT;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFEREXTENSION_HPP
