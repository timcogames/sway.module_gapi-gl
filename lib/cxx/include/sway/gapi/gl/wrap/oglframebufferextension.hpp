#ifndef SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFEREXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFEREXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

class OGLFramebufferExtension {
public:
  static core::TFunction<void(i32_t, u32_t *)> glGenFramebuffersEXT;
  static core::TFunction<void(i32_t, const u32_t *)> glDeleteFramebuffersEXT;
  static core::TFunction<void(u32_t, u32_t)> glBindFramebufferEXT;
  static core::TFunction<bool(u32_t)> glIsFramebufferEXT;
  static core::TFunction<void(u32_t, u32_t, u32_t, u32_t, i32_t)> glFramebufferTexture2DEXT;
  static core::TFunction<void(u32_t, u32_t, u32_t, u32_t)> glFramebufferRenderbufferEXT;
  static core::TFunction<u32_t(u32_t)> glCheckFramebufferStatusEXT;
  static core::TFunction<void(u32_t, u32_t, u32_t, i32_t *)> glGetFramebufferAttachmentParameterivEXT;

  static void define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &);
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFEREXTENSION_HPP
