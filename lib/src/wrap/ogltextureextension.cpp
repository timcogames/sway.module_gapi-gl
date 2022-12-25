#include <sway/gapi/gl/wrap/ogltextureextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, const void *)>
    OGLTextureExtension::glTextureImage2DEXT = nullptr;
core::binding::TFunction<void(u32_t)> OGLTextureExtension::glActiveTextureARB = nullptr;

void OGLTextureExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glTextureImage2DEXT = extensions({{"GL_EXT_direct_state_access", "glTextureImage2DEXT"}});
  glActiveTextureARB = extensions({{"GL_ARB_multitexture", "glActiveTextureARB"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
