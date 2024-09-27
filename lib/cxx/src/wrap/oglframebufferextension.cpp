#include <sway/gapi/gl/wrap/oglframebufferextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(i32_t, u32_t *)> OGLFramebufferExtension::glGenFramebuffersEXT = nullptr;
core::binding::TFunction<void(i32_t, const u32_t *)> OGLFramebufferExtension::glDeleteFramebuffersEXT = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OGLFramebufferExtension::glBindFramebufferEXT = nullptr;
core::binding::TFunction<bool(u32_t)> OGLFramebufferExtension::glIsFramebufferEXT = nullptr;
core::binding::TFunction<void(u32_t, u32_t, u32_t, u32_t, i32_t)> OGLFramebufferExtension::glFramebufferTexture2DEXT =
    nullptr;
core::binding::TFunction<void(u32_t, u32_t, u32_t, u32_t)> OGLFramebufferExtension::glFramebufferRenderbufferEXT =
    nullptr;
core::binding::TFunction<u32_t(u32_t)> OGLFramebufferExtension::glCheckFramebufferStatusEXT = nullptr;
core::binding::TFunction<void(u32_t, u32_t, u32_t, i32_t *)>
    OGLFramebufferExtension::glGetFramebufferAttachmentParameterivEXT = nullptr;

void OGLFramebufferExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glGenFramebuffersEXT = exts({{"GL_EXT_direct_state_access", "glGenFramebuffersEXT"}});
  glDeleteFramebuffersEXT = exts({{"GL_EXT_direct_state_access", "glDeleteFramebuffersEXT"}});
  glBindFramebufferEXT = exts({{"GL_EXT_direct_state_access", "glBindFramebufferEXT"}});
  glIsFramebufferEXT = exts({{"GL_EXT_direct_state_access", "glIsFramebufferEXT"}});
  glFramebufferTexture2DEXT = exts({{"GL_EXT_direct_state_access", "glFramebufferTexture2DEXT"}});
  glFramebufferRenderbufferEXT = exts({{"GL_EXT_direct_state_access", "glFramebufferRenderbufferEXT"}});
  glCheckFramebufferStatusEXT = exts({{"GL_EXT_direct_state_access", "glCheckFramebufferStatusEXT"}});
  glGetFramebufferAttachmentParameterivEXT =
      exts({{"GL_EXT_direct_state_access", "glGetFramebufferAttachmentParameterivEXT"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
