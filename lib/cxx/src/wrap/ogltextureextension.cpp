#include <sway/gapi/gl/wrap/ogltextureextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(i32_t, u32_t *)> OGLTextureExtension::glGenTexturesEXT = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OGLTextureExtension::glBindTextureEXT = nullptr;
core::binding::TFunction<void(u32_t, i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, const void *)>
    OGLTextureExtension::glTextureImage2DEXT = nullptr;
core::binding::TFunction<void(u32_t, i32_t, i32_t, i32_t, i32_t, i32_t, u32_t, u32_t, const void *)>
    OGLTextureExtension::glTexSubImage2DEXT = nullptr;
core::binding::TFunction<void(u32_t)> OGLTextureExtension::glActiveTextureARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t, const i32_t *)> OGLTextureExtension::glTexParameterIivEXT = nullptr;

void OGLTextureExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glGenTexturesEXT = extensions({{"GL_EXT_texture_object", "glGenTexturesEXT"}});
  glBindTextureEXT = extensions({{"GL_EXT_texture_object", "glBindTextureEXT"}});
  glTextureImage2DEXT = extensions({{"GL_EXT_direct_state_access", "glTextureImage2DEXT"}});
  glTexSubImage2DEXT = extensions({{"GL_EXT_subtexture", "glTexSubImage2DEXT"}});
  glActiveTextureARB = extensions({{"GL_ARB_multitexture", "glActiveTextureARB"}});
  glTexParameterIivEXT = extensions({{"GL_EXT_texture_integer", "glTexParameterIivEXT"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
