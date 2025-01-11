#include <sway/gapi/gl/wrap/oglrenderbufferextension.hpp>

namespace sway::gapi {

core::TFunction<void(i32_t, u32_t *)> OGLRenderBufferExtension::glGenRenderbuffersEXT = nullptr;
core::TFunction<void(i32_t, const u32_t *)> OGLRenderBufferExtension::glDeleteRenderbuffersEXT = nullptr;
core::TFunction<void(u32_t, u32_t)> OGLRenderBufferExtension::glBindRenderbufferEXT = nullptr;
core::TFunction<bool(u32_t)> OGLRenderBufferExtension::glIsRenderbufferEXT = nullptr;
core::TFunction<void(u32_t, u32_t, i32_t, i32_t)> OGLRenderBufferExtension::glRenderbufferStorageEXT = nullptr;
core::TFunction<void(u32_t, i32_t, u32_t, i32_t, i32_t)> OGLRenderBufferExtension::glRenderbufferStorageMultisampleEXT =
    nullptr;
core::TFunction<void(i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, u32_t, u32_t)>
    OGLRenderBufferExtension::glBlitFramebufferEXT = nullptr;
core::TFunction<void(u32_t, u32_t, i32_t *)> OGLRenderBufferExtension::glGetRenderbufferParameterivEXT = nullptr;

void OGLRenderBufferExtension::define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glGenRenderbuffersEXT = exts({{"GL_EXT_direct_state_access", "glGenRenderbuffersEXT"}});
  glDeleteRenderbuffersEXT = exts({{"GL_EXT_direct_state_access", "glDeleteRenderbuffersEXT"}});
  glBindRenderbufferEXT = exts({{"GL_EXT_direct_state_access", "glBindRenderbufferEXT"}});
  glIsRenderbufferEXT = exts({{"GL_EXT_direct_state_access", "glIsRenderbufferEXT"}});
  glRenderbufferStorageEXT = exts({{"GL_EXT_direct_state_access", "glRenderbufferStorageEXT"}});
  glRenderbufferStorageMultisampleEXT = exts({{"GL_EXT_direct_state_access", "glRenderbufferStorageMultisampleEXT"}});
  glBlitFramebufferEXT = exts({{"GL_EXT_direct_state_access", "glBlitFramebufferEXT"}});
  glGetRenderbufferParameterivEXT = exts({{"GL_EXT_direct_state_access", "glGetRenderbufferParameterivEXT"}});
}

}  // namespace sway::gapi
