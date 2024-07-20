#include <sway/gapi/gl/wrap/oglgenericshaderextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<u32_t(u32_t)> OGLGenericShaderExtension::glCreateShaderObjectARB = nullptr;
core::binding::TFunction<void(u32_t)> OGLGenericShaderExtension::glDeleteObjectARB = nullptr;
core::binding::TFunction<void(u32_t, i32_t, lpcstr_t *, const i32_t *)> OGLGenericShaderExtension::glShaderSourceARB =
    nullptr;
core::binding::TFunction<void(u32_t)> OGLGenericShaderExtension::glCompileShaderARB = nullptr;
core::binding::TFunction<i32_t(u32_t, lpcstr_t)> OGLGenericShaderExtension::glGetAttribLocationARB = nullptr;

void OGLGenericShaderExtension::define(
    const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glCreateShaderObjectARB = extensions({{"GL_ARB_shader_objects", "glCreateShaderObjectARB"}});
  glDeleteObjectARB = extensions({{"GL_ARB_shader_objects", "glDeleteObjectARB"}});
  glShaderSourceARB = extensions({{"GL_ARB_shader_objects", "glShaderSourceARB"}});
  glCompileShaderARB = extensions({{"GL_ARB_shader_objects", "glCompileShaderARB"}});
  glGetAttribLocationARB = extensions({{"GL_ARB_vertex_shader", "glGetAttribLocationARB"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
