#include <sway/gapi/gl/wrap/oglshaderprogramextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<u32_t()> OGLShaderProgramExtension::glCreateProgramObjectARB = nullptr;
core::binding::TFunction<void(s32_t, const u32_t *)> OGLShaderProgramExtension::glDeleteProgramsARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OGLShaderProgramExtension::glAttachObjectARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OGLShaderProgramExtension::glDetachObjectARB = nullptr;
core::binding::TFunction<void(u32_t)> OGLShaderProgramExtension::glLinkProgramARB = nullptr;
core::binding::TFunction<void(u32_t)> OGLShaderProgramExtension::glValidateProgramARB = nullptr;
core::binding::TFunction<void(u32_t)> OGLShaderProgramExtension::glUseProgramObjectARB = nullptr;
core::binding::TFunction<s32_t(u32_t, lpcstr_t)> OGLShaderProgramExtension::glGetUniformLocationARB = nullptr;
core::binding::TFunction<void(s32_t, s32_t)> OGLShaderProgramExtension::glUniform1iARB = nullptr;
core::binding::TFunction<void(s32_t, f32_t)> OGLShaderProgramExtension::glUniform1fARB = nullptr;
core::binding::TFunction<void(s32_t, f32_t, f32_t, f32_t, f32_t)> OGLShaderProgramExtension::glUniform4fARB = nullptr;
core::binding::TFunction<void(s32_t, s32_t, bool, const f32_t *)> OGLShaderProgramExtension::glUniformMatrix4fvARB =
    nullptr;

void OGLShaderProgramExtension::define(
    const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glCreateProgramObjectARB = extensions({{"GL_ARB_shader_objects", "glCreateProgramObjectARB"}});
  glDeleteProgramsARB = extensions({{"GL_ARB_fragment_program", "glDeleteProgramsARB"}});
  glAttachObjectARB = extensions({{"GL_ARB_shader_objects", "glAttachObjectARB"}});
  glDetachObjectARB = extensions({{"GL_ARB_shader_objects", "glDetachObjectARB"}});
  glLinkProgramARB = extensions({{"GL_ARB_shader_objects", "glLinkProgramARB"}});
  glValidateProgramARB = extensions({{"GL_ARB_shader_objects", "glValidateProgramARB"}});
  glUseProgramObjectARB = extensions({{"GL_ARB_shader_objects", "glUseProgramObjectARB"}});
  glGetUniformLocationARB = extensions({{"GL_ARB_shader_objects", "glGetUniformLocationARB"}});
  glUniform1iARB = extensions({{"GL_ARB_shader_objects", "glUniform1iARB"}});
  glUniform1fARB = extensions({{"GL_ARB_shader_objects", "glUniform1fARB"}});
  glUniform4fARB = extensions({{"GL_ARB_shader_objects", "glUniform4fARB"}});
  glUniformMatrix4fvARB = extensions({{"GL_ARB_shader_objects", "glUniformMatrix4fvARB"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
