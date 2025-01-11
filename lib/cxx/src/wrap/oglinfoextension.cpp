#include <sway/gapi/gl/wrap/oglinfoextension.hpp>

namespace sway::gapi {

core::TFunction<void(u32_t, u32_t, i32_t *)> OGLInfoExtension::glGetObjectParameterivARB = nullptr;
core::TFunction<void(u32_t, i32_t, i32_t *, lpstr_t)> OGLInfoExtension::glGetInfoLogARB = nullptr;

void OGLInfoExtension::define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glGetObjectParameterivARB = exts({{"GL_ARB_shader_objects", "glGetObjectParameterivARB"}});
  glGetInfoLogARB = exts({{"GL_ARB_shader_objects", "glGetInfoLogARB"}});
}

}  // namespace sway::gapi
