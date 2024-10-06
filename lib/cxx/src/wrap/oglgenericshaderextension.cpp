#include <sway/gapi/gl/wrap/oglgenericshaderextension.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

core::binding::TFunction<u32_t(u32_t)> OGLGenericShaderExtension::glCreateShaderObjectARB = nullptr;
core::binding::TFunction<void(u32_t)> OGLGenericShaderExtension::glDeleteObjectARB = nullptr;
core::binding::TFunction<void(u32_t, i32_t, lpcstr_t *, const i32_t *)> OGLGenericShaderExtension::glShaderSourceARB =
    nullptr;
core::binding::TFunction<void(u32_t)> OGLGenericShaderExtension::glCompileShaderARB = nullptr;
core::binding::TFunction<i32_t(u32_t, lpcstr_t)> OGLGenericShaderExtension::glGetAttribLocationARB = nullptr;

void OGLGenericShaderExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glCreateShaderObjectARB = exts({{"GL_ARB_shader_objects", "glCreateShaderObjectARB"}});
  glDeleteObjectARB = exts({{"GL_ARB_shader_objects", "glDeleteObjectARB"}});
  glShaderSourceARB = exts({{"GL_ARB_shader_objects", "glShaderSourceARB"}});
  glCompileShaderARB = exts({{"GL_ARB_shader_objects", "glCompileShaderARB"}});
  glGetAttribLocationARB = exts({{"GL_ARB_vertex_shader", "glGetAttribLocationARB"}});
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
