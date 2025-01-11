#include <sway/gapi/gl/wrap/oglgenericshaderextension.hpp>

namespace sway::gapi {

core::TFunction<u32_t(u32_t)> OGLGenericShaderExtension::glCreateShaderObjectARB = nullptr;
core::TFunction<void(u32_t)> OGLGenericShaderExtension::glDeleteObjectARB = nullptr;
core::TFunction<void(u32_t, i32_t, lpcstr_t *, const i32_t *)> OGLGenericShaderExtension::glShaderSourceARB = nullptr;
core::TFunction<void(u32_t)> OGLGenericShaderExtension::glCompileShaderARB = nullptr;
core::TFunction<i32_t(u32_t, lpcstr_t)> OGLGenericShaderExtension::glGetAttribLocationARB = nullptr;

void OGLGenericShaderExtension::define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glCreateShaderObjectARB = exts({{"GL_ARB_shader_objects", "glCreateShaderObjectARB"}});
  glDeleteObjectARB = exts({{"GL_ARB_shader_objects", "glDeleteObjectARB"}});
  glShaderSourceARB = exts({{"GL_ARB_shader_objects", "glShaderSourceARB"}});
  glCompileShaderARB = exts({{"GL_ARB_shader_objects", "glCompileShaderARB"}});
  glGetAttribLocationARB = exts({{"GL_ARB_vertex_shader", "glGetAttribLocationARB"}});
}

}  // namespace sway::gapi
