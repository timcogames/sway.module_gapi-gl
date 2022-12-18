#include <sway/gapi/gl/capability.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/shaderprogramhelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

ShaderProgramHelper::ShaderProgramHelper(std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> exts)
    : extensions_(std::move(exts)) {

#ifdef _STUB
  CreateProgram_ = &ShaderProgramHelper::EMU_CreateProgram;
  DeleteProgram_ = &ShaderProgramHelper::EMU_DeleteProgram;
  AttachShader_ = &ShaderProgramHelper::EMU_AttachShader;
  DetachShader_ = &ShaderProgramHelper::EMU_DetachShader;
  LinkProgram_ = &ShaderProgramHelper::EMU_LinkProgram;
  ValidateProgram_ = &ShaderProgramHelper::EMU_ValidateProgram;
  UseProgram_ = &ShaderProgramHelper::EMU_UseProgram;
  GetUniformLocation_ = &ShaderProgramHelper::EMU_GetUniformLocation;
  Uniform4f_ = &ShaderProgramHelper::EMU_Uniform4f;
  UniformMatrix4f_ = &ShaderProgramHelper::EMU_UniformMatrix4f;
  GetObjectParam_ = &ShaderProgramHelper::EMU_GetObjectParam;
#else

  const auto *extensions = Capability::getExtensions();
  if (Capability::isExtensionSupported(extensions, "GL_ARB_shader_objects")) {
    CreateProgram_ = &ShaderProgramHelper::ARB_CreateProgram;
    DeleteProgram_ = &ShaderProgramHelper::ARB_DeleteProgram;
    AttachShader_ = &ShaderProgramHelper::ARB_AttachShader;
    DetachShader_ = &ShaderProgramHelper::ARB_DetachShader;
    LinkProgram_ = &ShaderProgramHelper::ARB_LinkProgram;
    ValidateProgram_ = &ShaderProgramHelper::ARB_ValidateProgram;
    UseProgram_ = &ShaderProgramHelper::ARB_UseProgram;
    GetUniformLocation_ = &ShaderProgramHelper::ARB_GetUniformLocation;
    Uniform4f_ = &ShaderProgramHelper::ARB_Uniform4f;
    UniformMatrix4f_ = &ShaderProgramHelper::ARB_UniformMatrix4f;
    GetObjectParam_ = &ShaderProgramHelper::ARB_GetObjectParam;
  } else {
    CreateProgram_ = &ShaderProgramHelper::STD_CreateProgram;
    DeleteProgram_ = &ShaderProgramHelper::STD_DeleteProgram;
    AttachShader_ = &ShaderProgramHelper::STD_AttachShader;
    DetachShader_ = &ShaderProgramHelper::STD_DetachShader;
    LinkProgram_ = &ShaderProgramHelper::STD_LinkProgram;
    ValidateProgram_ = &ShaderProgramHelper::STD_ValidateProgram;
    UseProgram_ = &ShaderProgramHelper::STD_UseProgram;
    GetUniformLocation_ = &ShaderProgramHelper::STD_GetUniformLocation;
    Uniform4f_ = &ShaderProgramHelper::STD_Uniform4f;
    UniformMatrix4f_ = &ShaderProgramHelper::STD_UniformMatrix4f;
    GetObjectParam_ = &ShaderProgramHelper::STD_GetObjectParam;
  }

#endif
}

auto ShaderProgramHelper::EMU_CreateProgram() -> u32_t { return 0; }

auto ShaderProgramHelper::STD_CreateProgram() -> u32_t { return glCreateProgram(); }

auto ShaderProgramHelper::ARB_CreateProgram() -> u32_t {
  // core::binding::TFunction<u32_t()> callbackFunc = extensions_({{"GL_ARB_shader_objects",
  // "glCreateProgramObjectARB"}});

  // return callbackFunc();
  return Extension::glCreateProgramObject();
}

void ShaderProgramHelper::EMU_DeleteProgram([[maybe_unused]] s32_t num, [[maybe_unused]] const u32_t *programs) {}

void ShaderProgramHelper::STD_DeleteProgram([[maybe_unused]] s32_t num, const u32_t *programs) {
  glDeleteProgram(programs[0]);
}

void ShaderProgramHelper::ARB_DeleteProgram(s32_t num, const u32_t *programs) {
  // core::binding::TFunction<void(s32_t, const u32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_fragment_program", "glDeleteProgramsARB"}});

  // callbackFunc(num, programs);

  Extension::glDeletePrograms(num, programs);
}

void ShaderProgramHelper::EMU_AttachShader([[maybe_unused]] u32_t program, [[maybe_unused]] u32_t shader) {}

void ShaderProgramHelper::STD_AttachShader(u32_t program, u32_t shader) { glAttachShader(program, shader); }

void ShaderProgramHelper::ARB_AttachShader(u32_t program, u32_t shader) {
  // core::binding::TFunction<void(u32_t, u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glAttachObjectARB"}});

  // callbackFunc(program, shader);

  Extension::glAttachObject(program, shader);
}

void ShaderProgramHelper::EMU_DetachShader([[maybe_unused]] u32_t program, [[maybe_unused]] u32_t shader) {}

void ShaderProgramHelper::STD_DetachShader(u32_t program, u32_t shader) { glDetachShader(program, shader); }

void ShaderProgramHelper::ARB_DetachShader(u32_t program, u32_t shader) {
  // core::binding::TFunction<void(u32_t, u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glDetachObjectARB"}});

  // callbackFunc(program, shader);

  Extension::glDetachObject(program, shader);
}

void ShaderProgramHelper::EMU_LinkProgram([[maybe_unused]] u32_t program) {}

void ShaderProgramHelper::STD_LinkProgram(u32_t program) { glLinkProgram(program); }

void ShaderProgramHelper::ARB_LinkProgram(u32_t program) {
  // core::binding::TFunction<void(u32_t)> callbackFunc = extensions_({{"GL_ARB_shader_objects", "glLinkProgramARB"}});

  // callbackFunc(program);

  Extension::glLinkProgram(program);
}

void ShaderProgramHelper::EMU_ValidateProgram([[maybe_unused]] u32_t program) {}

void ShaderProgramHelper::STD_ValidateProgram(u32_t program) { glValidateProgram(program); }

void ShaderProgramHelper::ARB_ValidateProgram(u32_t program) {
  // core::binding::TFunction<void(u32_t)> callbackFunc = extensions_({{"GL_ARB_shader_objects",
  // "glValidateProgramARB"}});

  // callbackFunc(program);

  Extension::glValidateProgram(program);
}

void ShaderProgramHelper::EMU_UseProgram([[maybe_unused]] u32_t program) {}

void ShaderProgramHelper::STD_UseProgram(u32_t program) { glUseProgram(program); }

void ShaderProgramHelper::ARB_UseProgram(u32_t program) {
  // core::binding::TFunction<void(u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glUseProgramObjectARB"}});

  // callbackFunc(program);

  Extension::glUseProgramObject(program);
}

auto ShaderProgramHelper::EMU_GetUniformLocation([[maybe_unused]] u32_t program, [[maybe_unused]] lpcstr_t name)
    -> s32_t {
  return 0;
}

auto ShaderProgramHelper::STD_GetUniformLocation(u32_t program, lpcstr_t name) -> s32_t {
  return glGetUniformLocation(program, name);
}

auto ShaderProgramHelper::ARB_GetUniformLocation(u32_t program, lpcstr_t name) -> s32_t {
  // core::binding::TFunction<s32_t(u32_t, lpcstr_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glGetUniformLocationARB"}});

  // return callbackFunc(program, name);

  Extension::glGetUniformLocation(program, name);
}

void ShaderProgramHelper::EMU_Uniform4f([[maybe_unused]] s32_t location, [[maybe_unused]] f32_t v0,
    [[maybe_unused]] f32_t v1, [[maybe_unused]] f32_t v2, [[maybe_unused]] f32_t v3) {}

void ShaderProgramHelper::STD_Uniform4f(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3) {
  glUniform4f(location, v0, v1, v2, v3);
}

void ShaderProgramHelper::ARB_Uniform4f(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3) {
  // core::binding::TFunction<void(s32_t, f32_t, f32_t, f32_t, f32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glUniform4fARB"}});

  // callbackFunc(location, v0, v1, v2, v3);

  Extension::glUniform4f(location, v0, v1, v2, v3);
}

void ShaderProgramHelper::EMU_UniformMatrix4f([[maybe_unused]] s32_t location, [[maybe_unused]] s32_t count,
    [[maybe_unused]] bool transpose, [[maybe_unused]] const f32_t *value) {}

void ShaderProgramHelper::STD_UniformMatrix4f(s32_t location, s32_t count, bool transpose, const f32_t *value) {
  glUniformMatrix4fv(location, count, transpose, value);
}

void ShaderProgramHelper::ARB_UniformMatrix4f(s32_t location, s32_t count, bool transpose, const f32_t *value) {
  // core::binding::TFunction<void(s32_t, s32_t, bool, const f32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glUniformMatrix4fvARB"}});

  // callbackFunc(location, count, transpose, value);

  Extension::glUniformMatrix4fv(location, count, transpose, value);
}

void ShaderProgramHelper::EMU_GetObjectParam(u32_t program, u32_t pname, s32_t *params) {}

void ShaderProgramHelper::STD_GetObjectParam(u32_t program, u32_t pname, s32_t *params) {
  glGetProgramiv(program, pname, params);
}

void ShaderProgramHelper::ARB_GetObjectParam(u32_t program, u32_t pname, s32_t *params) {
  // core::binding::TFunction<void(u32_t, u32_t, s32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glGetObjectParameterivARB"}});

  // callbackFunc(program, pname, params);

  Extension::glGetObjectParameteriv(program, pname, params);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
