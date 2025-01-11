#ifndef SWAY_GAPI_GL_WRAP_OGLRENDERBUFFEREXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLRENDERBUFFEREXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

class OGLRenderBufferExtension {
public:
  static core::TFunction<void(i32_t, u32_t *)> glGenRenderbuffersEXT;
  static core::TFunction<void(i32_t, const u32_t *)> glDeleteRenderbuffersEXT;
  static core::TFunction<void(u32_t, u32_t)> glBindRenderbufferEXT;
  static core::TFunction<bool(u32_t)> glIsRenderbufferEXT;
  static core::TFunction<void(u32_t, u32_t, i32_t, i32_t)> glRenderbufferStorageEXT;
  static core::TFunction<void(u32_t, i32_t, u32_t, i32_t, i32_t)> glRenderbufferStorageMultisampleEXT;
  static core::TFunction<void(i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, u32_t, u32_t)>
      glBlitFramebufferEXT;
  static core::TFunction<void(u32_t, u32_t, i32_t *)> glGetRenderbufferParameterivEXT;

  static void define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &);
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_OGLRENDERBUFFEREXTENSION_HPP
