#ifndef SWAY_GAPI_GL_WRAP_OGLRENDERBUFFEREXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLRENDERBUFFEREXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLRenderBufferExtension {
public:
  static core::binding::TFunction<void(i32_t, u32_t *)> glGenRenderbuffersEXT;
  static core::binding::TFunction<void(i32_t, const u32_t *)> glDeleteRenderbuffersEXT;
  static core::binding::TFunction<void(u32_t, u32_t)> glBindRenderbufferEXT;
  static core::binding::TFunction<bool(u32_t)> glIsRenderbufferEXT;
  static core::binding::TFunction<void(u32_t, u32_t, i32_t, i32_t)> glRenderbufferStorageEXT;
  static core::binding::TFunction<void(u32_t, i32_t, u32_t, i32_t, i32_t)> glRenderbufferStorageMultisampleEXT;
  static core::binding::TFunction<void(i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, u32_t, u32_t)>
      glBlitFramebufferEXT;
  static core::binding::TFunction<void(u32_t, u32_t, i32_t *)> glGetRenderbufferParameterivEXT;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_WRAP_OGLRENDERBUFFEREXTENSION_HPP
