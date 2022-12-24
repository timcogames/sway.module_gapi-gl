#include <sway/gapi/gl/wrap/ogltextureextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(s32_t target, s32_t level, s32_t internalFormat, s32_t width, s32_t height, s32_t border,
    s32_t format, s32_t type, const void *pixels)>
    OGLTextureExtension::glTextureImage2DEXT = nullptr;

void OGLTextureExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glTextureImage2DEXT = extensions({{"GL_EXT_direct_state_access", "glTextureImage2DEXT"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
