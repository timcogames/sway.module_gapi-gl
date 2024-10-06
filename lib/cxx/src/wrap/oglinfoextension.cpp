#include <sway/gapi/gl/wrap/oglinfoextension.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

core::binding::TFunction<void(u32_t, u32_t, i32_t *)> OGLInfoExtension::glGetObjectParameterivARB = nullptr;
core::binding::TFunction<void(u32_t, i32_t, i32_t *, lpstr_t)> OGLInfoExtension::glGetInfoLogARB = nullptr;

void OGLInfoExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glGetObjectParameterivARB = exts({{"GL_ARB_shader_objects", "glGetObjectParameterivARB"}});
  glGetInfoLogARB = exts({{"GL_ARB_shader_objects", "glGetInfoLogARB"}});
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
