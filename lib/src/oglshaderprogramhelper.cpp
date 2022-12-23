#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/oglshaderprogramhelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLShaderProgramHelper::OGLShaderProgramHelper(std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> exts)
    : extensions_(std::move(exts)) {

#ifdef _STUB
  CreateProgram_ = &OGLShaderProgramHelper::EMU_CreateProgram;
  DeleteProgram_ = &OGLShaderProgramHelper::EMU_DeleteProgram;
  AttachShader_ = &OGLShaderProgramHelper::EMU_AttachShader;
  DetachShader_ = &OGLShaderProgramHelper::EMU_DetachShader;
  LinkProgram_ = &OGLShaderProgramHelper::EMU_LinkProgram;
  ValidateProgram_ = &OGLShaderProgramHelper::EMU_ValidateProgram;
  UseProgram_ = &OGLShaderProgramHelper::EMU_UseProgram;
  GetUniformLocation_ = &OGLShaderProgramHelper::EMU_GetUniformLocation;
  Uniform4f_ = &OGLShaderProgramHelper::EMU_Uniform4f;
  UniformMatrix4f_ = &OGLShaderProgramHelper::EMU_UniformMatrix4f;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_shader_objects")) {
    CreateProgram_ = &OGLShaderProgramHelper::ARB_CreateProgram;
    DeleteProgram_ = &OGLShaderProgramHelper::ARB_DeleteProgram;
    AttachShader_ = &OGLShaderProgramHelper::ARB_AttachShader;
    DetachShader_ = &OGLShaderProgramHelper::ARB_DetachShader;
    LinkProgram_ = &OGLShaderProgramHelper::ARB_LinkProgram;
    ValidateProgram_ = &OGLShaderProgramHelper::ARB_ValidateProgram;
    UseProgram_ = &OGLShaderProgramHelper::ARB_UseProgram;
    GetUniformLocation_ = &OGLShaderProgramHelper::ARB_GetUniformLocation;
    Uniform4f_ = &OGLShaderProgramHelper::ARB_Uniform4f;
    UniformMatrix4f_ = &OGLShaderProgramHelper::ARB_UniformMatrix4f;
  } else {
    CreateProgram_ = &OGLShaderProgramHelper::STD_CreateProgram;
    DeleteProgram_ = &OGLShaderProgramHelper::STD_DeleteProgram;
    AttachShader_ = &OGLShaderProgramHelper::STD_AttachShader;
    DetachShader_ = &OGLShaderProgramHelper::STD_DetachShader;
    LinkProgram_ = &OGLShaderProgramHelper::STD_LinkProgram;
    ValidateProgram_ = &OGLShaderProgramHelper::STD_ValidateProgram;
    UseProgram_ = &OGLShaderProgramHelper::STD_UseProgram;
    GetUniformLocation_ = &OGLShaderProgramHelper::STD_GetUniformLocation;
    Uniform4f_ = &OGLShaderProgramHelper::STD_Uniform4f;
    UniformMatrix4f_ = &OGLShaderProgramHelper::STD_UniformMatrix4f;
  }

#endif
}

auto OGLShaderProgramHelper::EMU_CreateProgram() -> u32_t { return 0; }

auto OGLShaderProgramHelper::STD_CreateProgram() -> u32_t { return glCreateProgram(); }

auto OGLShaderProgramHelper::ARB_CreateProgram() -> u32_t {
  // core::binding::TFunction<u32_t()> callbackFunc = extensions_({{"GL_ARB_shader_objects",
  // "glCreateProgramObjectARB"}});

  // return callbackFunc();
  return Extension::glCreateProgramObject();
}

void OGLShaderProgramHelper::EMU_DeleteProgram([[maybe_unused]] s32_t num, [[maybe_unused]] const u32_t *programs) {}

void OGLShaderProgramHelper::STD_DeleteProgram([[maybe_unused]] s32_t num, const u32_t *programs) {
  glDeleteProgram(programs[0]);
}

void OGLShaderProgramHelper::ARB_DeleteProgram(s32_t num, const u32_t *programs) {
  // core::binding::TFunction<void(s32_t, const u32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_fragment_program", "glDeleteProgramsARB"}});

  // callbackFunc(num, programs);

  Extension::glDeletePrograms(num, programs);
}

void OGLShaderProgramHelper::EMU_AttachShader(
    [[maybe_unused]] std::optional<u32_t> progId, [[maybe_unused]] std::optional<u32_t> shaderId) {}

void OGLShaderProgramHelper::STD_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId) {
  glAttachShader(progId.value(), shaderId.value());
}

void OGLShaderProgramHelper::ARB_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId) {
  // core::binding::TFunction<void(u32_t, u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glAttachObjectARB"}});

  // callbackFunc(progId.value(), shaderId);

  Extension::glAttachObject(progId.value(), shaderId.value());
}

void OGLShaderProgramHelper::EMU_DetachShader(
    [[maybe_unused]] std::optional<u32_t> progId, [[maybe_unused]] std::optional<u32_t> shaderId) {}

void OGLShaderProgramHelper::STD_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId) {
  glDetachShader(progId.value(), shaderId.value());
}

void OGLShaderProgramHelper::ARB_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId) {
  // core::binding::TFunction<void(u32_t, u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glDetachObjectARB"}});

  // callbackFunc(progId.value(), shader);

  Extension::glDetachObject(progId.value(), shaderId.value());
}

void OGLShaderProgramHelper::EMU_LinkProgram([[maybe_unused]] std::optional<u32_t> progId, s32_t *status) {}

void OGLShaderProgramHelper::STD_LinkProgram(std::optional<u32_t> progId, s32_t *status) {
  glLinkProgram(progId.value());
  glGetProgramiv(progId.value(), GL_LINK_STATUS, status);
}

void OGLShaderProgramHelper::ARB_LinkProgram(std::optional<u32_t> progId, s32_t *status) {
  // core::binding::TFunction<void(u32_t)> callbackFunc = extensions_({{"GL_ARB_shader_objects", "glLinkProgramARB"}});

  // callbackFunc(progId.value());

  Extension::glLinkProgram(progId.value());
  Extension::glGetObjectParameteriv(progId.value(), GL_OBJECT_LINK_STATUS_ARB, status);
}

void OGLShaderProgramHelper::EMU_ValidateProgram(
    [[maybe_unused]] std::optional<u32_t> progId, [[maybe_unused]] s32_t *status) {}

void OGLShaderProgramHelper::STD_ValidateProgram(std::optional<u32_t> progId, s32_t *status) {
  glValidateProgram(progId.value());
  glGetProgramiv(progId.value(), GL_VALIDATE_STATUS, status);
}

void OGLShaderProgramHelper::ARB_ValidateProgram(std::optional<u32_t> progId, s32_t *status) {
  // core::binding::TFunction<void(u32_t)> callbackFunc = extensions_({{"GL_ARB_shader_objects",
  // "glValidateProgramARB"}});

  // callbackFunc(progId.value());

  Extension::glValidateProgram(progId.value());
  Extension::glGetObjectParameteriv(progId.value(), GL_OBJECT_VALIDATE_STATUS_ARB, status);
}

void OGLShaderProgramHelper::EMU_UseProgram([[maybe_unused]] std::optional<u32_t> progId) {}

void OGLShaderProgramHelper::STD_UseProgram(std::optional<u32_t> progId) { glUseProgram(progId.value()); }

void OGLShaderProgramHelper::ARB_UseProgram(std::optional<u32_t> progId) {
  // core::binding::TFunction<void(u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glUseProgramObjectARB"}});

  // callbackFunc(progId.value());

  Extension::glUseProgramObject(progId.value());
}

auto OGLShaderProgramHelper::EMU_GetUniformLocation(
    [[maybe_unused]] std::optional<u32_t> progId, [[maybe_unused]] lpcstr_t name) -> s32_t {
  return 0;
}

auto OGLShaderProgramHelper::STD_GetUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t {
  return glGetUniformLocation(progId.value(), name);
}

auto OGLShaderProgramHelper::ARB_GetUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t {
  // core::binding::TFunction<s32_t(u32_t, lpcstr_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glGetUniformLocationARB"}});

  // return callbackFunc(progId.value(), name);

  Extension::glGetUniformLocation(progId.value(), name);
}

void OGLShaderProgramHelper::EMU_Uniform4f([[maybe_unused]] s32_t location, [[maybe_unused]] f32_t v0,
    [[maybe_unused]] f32_t v1, [[maybe_unused]] f32_t v2, [[maybe_unused]] f32_t v3) {}

void OGLShaderProgramHelper::STD_Uniform4f(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3) {
  glUniform4f(location, v0, v1, v2, v3);
}

void OGLShaderProgramHelper::ARB_Uniform4f(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3) {
  // core::binding::TFunction<void(s32_t, f32_t, f32_t, f32_t, f32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glUniform4fARB"}});

  // callbackFunc(location, v0, v1, v2, v3);

  Extension::glUniform4f(location, v0, v1, v2, v3);
}

void OGLShaderProgramHelper::EMU_UniformMatrix4f([[maybe_unused]] s32_t location, [[maybe_unused]] s32_t count,
    [[maybe_unused]] bool transpose, [[maybe_unused]] const f32_t *value) {}

void OGLShaderProgramHelper::STD_UniformMatrix4f(s32_t location, s32_t count, bool transpose, const f32_t *value) {
  glUniformMatrix4fv(location, count, transpose, value);
}

void OGLShaderProgramHelper::ARB_UniformMatrix4f(s32_t location, s32_t count, bool transpose, const f32_t *value) {
  // core::binding::TFunction<void(s32_t, s32_t, bool, const f32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glUniformMatrix4fvARB"}});

  // callbackFunc(location, count, transpose, value);

  Extension::glUniformMatrix4fv(location, count, transpose, value);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
