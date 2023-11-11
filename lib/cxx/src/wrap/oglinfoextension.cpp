#include <sway/gapi/gl/wrap/oglinfoextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(u32_t, u32_t, s32_t *)> OGLInfoExtension::glGetObjectParameterivARB = nullptr;
core::binding::TFunction<void(u32_t, s32_t, s32_t *, lpstr_t)> OGLInfoExtension::glGetInfoLogARB = nullptr;

void OGLInfoExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glGetObjectParameterivARB = extensions({{"GL_ARB_shader_objects", "glGetObjectParameterivARB"}});
  glGetInfoLogARB = extensions({{"GL_ARB_shader_objects", "glGetInfoLogARB"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
