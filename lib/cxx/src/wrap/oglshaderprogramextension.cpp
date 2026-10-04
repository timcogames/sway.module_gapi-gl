#include <sway/gapi/gl/wrap/oglshaderprogramextension.hpp>

namespace sway::gapi {

core::TFunctionPointer<u32_t()> OGLShaderProgramExtension::glCreateProgramObjectARB = nullptr;
core::TFunctionPointer<void(i32_t, const u32_t *)> OGLShaderProgramExtension::glDeleteProgramsARB = nullptr;
core::TFunctionPointer<void(u32_t, u32_t)> OGLShaderProgramExtension::glAttachObjectARB = nullptr;
core::TFunctionPointer<void(u32_t, u32_t)> OGLShaderProgramExtension::glDetachObjectARB = nullptr;
core::TFunctionPointer<void(u32_t)> OGLShaderProgramExtension::glLinkProgramARB = nullptr;
core::TFunctionPointer<void(u32_t)> OGLShaderProgramExtension::glValidateProgramARB = nullptr;
core::TFunctionPointer<void(u32_t)> OGLShaderProgramExtension::glUseProgramObjectARB = nullptr;
core::TFunctionPointer<i32_t(u32_t, lpcstr_t)> OGLShaderProgramExtension::glGetUniformLocationARB = nullptr;
core::TFunctionPointer<void(i32_t, i32_t)> OGLShaderProgramExtension::glUniform1iARB = nullptr;
core::TFunctionPointer<void(i32_t, f32_t)> OGLShaderProgramExtension::glUniform1fARB = nullptr;
core::TFunctionPointer<void(i32_t, f32_t, f32_t, f32_t, f32_t)> OGLShaderProgramExtension::glUniform4fARB = nullptr;
core::TFunctionPointer<void(i32_t, i32_t, f32_t *)> OGLShaderProgramExtension::glUniform4fvARB = nullptr;
core::TFunctionPointer<void(i32_t, i32_t, bool, const f32_t *)> OGLShaderProgramExtension::glUniformMatrix4fvARB =
    nullptr;

void OGLShaderProgramExtension::define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glCreateProgramObjectARB = exts({{"GL_ARB_shader_objects", "glCreateProgramObjectARB"}});
  glDeleteProgramsARB = exts({{"GL_ARB_fragment_program", "glDeleteProgramsARB"}});
  glAttachObjectARB = exts({{"GL_ARB_shader_objects", "glAttachObjectARB"}});
  glDetachObjectARB = exts({{"GL_ARB_shader_objects", "glDetachObjectARB"}});
  glLinkProgramARB = exts({{"GL_ARB_shader_objects", "glLinkProgramARB"}});
  glValidateProgramARB = exts({{"GL_ARB_shader_objects", "glValidateProgramARB"}});
  glUseProgramObjectARB = exts({{"GL_ARB_shader_objects", "glUseProgramObjectARB"}});
  glGetUniformLocationARB = exts({{"GL_ARB_shader_objects", "glGetUniformLocationARB"}});
  glUniform1iARB = exts({{"GL_ARB_shader_objects", "glUniform1iARB"}});
  glUniform1fARB = exts({{"GL_ARB_shader_objects", "glUniform1fARB"}});
  glUniform4fARB = exts({{"GL_ARB_shader_objects", "glUniform4fARB"}});
  glUniform4fvARB = exts({{"GL_ARB_shader_objects", "glUniform4fvARB"}});
  glUniformMatrix4fvARB = exts({{"GL_ARB_shader_objects", "glUniformMatrix4fvARB"}});
}

}  // namespace sway::gapi
