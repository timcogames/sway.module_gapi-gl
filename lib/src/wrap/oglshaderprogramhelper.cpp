#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramextension.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramhelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLShaderProgramHelper::OGLShaderProgramHelper() {
#ifdef _STUB
  CreateProgram_ = &OGLShaderProgramHelper::EMU_CreateProgram;
  DeleteProgram_ = &OGLShaderProgramHelper::EMU_DeleteProgram;
  AttachShader_ = &OGLShaderProgramHelper::EMU_AttachShader;
  DetachShader_ = &OGLShaderProgramHelper::EMU_DetachShader;
  LinkProgram_ = &OGLShaderProgramHelper::EMU_LinkProgram;
  ValidateProgram_ = &OGLShaderProgramHelper::EMU_ValidateProgram;
  UseProgram_ = &OGLShaderProgramHelper::EMU_UseProgram;
  getUniformLocation_ = &OGLShaderProgramHelper::EMU_getUniformLocation;
  setUniform4f_ = &OGLShaderProgramHelper::EMU_setUniform4f;
  setUniformMatrix4f_ = &OGLShaderProgramHelper::EMU_setUniformMatrix4f;
  setUniform1i_ = &OGLShaderProgramHelper::EMU_setUniform1i;
  setUniform1f_ = &OGLShaderProgramHelper::EMU_setUniform1f;
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
    getUniformLocation_ = &OGLShaderProgramHelper::ARB_getUniformLocation;
    setUniform4f_ = &OGLShaderProgramHelper::ARB_setUniform4f;
    setUniformMatrix4f_ = &OGLShaderProgramHelper::ARB_setUniformMatrix4f;
    setUniform1i_ = &OGLShaderProgramHelper::ARB_setUniform1i;
    setUniform1f_ = &OGLShaderProgramHelper::ARB_setUniform1f;
  } else {
    CreateProgram_ = &OGLShaderProgramHelper::STD_CreateProgram;
    DeleteProgram_ = &OGLShaderProgramHelper::STD_DeleteProgram;
    AttachShader_ = &OGLShaderProgramHelper::STD_AttachShader;
    DetachShader_ = &OGLShaderProgramHelper::STD_DetachShader;
    LinkProgram_ = &OGLShaderProgramHelper::STD_LinkProgram;
    ValidateProgram_ = &OGLShaderProgramHelper::STD_ValidateProgram;
    UseProgram_ = &OGLShaderProgramHelper::STD_UseProgram;
    getUniformLocation_ = &OGLShaderProgramHelper::STD_getUniformLocation;
    setUniform4f_ = &OGLShaderProgramHelper::STD_setUniform4f;
    setUniformMatrix4f_ = &OGLShaderProgramHelper::STD_setUniformMatrix4f;
    setUniform1i_ = &OGLShaderProgramHelper::STD_setUniform1i;
    setUniform1f_ = &OGLShaderProgramHelper::STD_setUniform1f;
  }

#endif
}

auto OGLShaderProgramHelper::EMU_CreateProgram() -> u32_t { return 0; }

auto OGLShaderProgramHelper::STD_CreateProgram() -> u32_t { return glCreateProgram(); }

auto OGLShaderProgramHelper::ARB_CreateProgram() -> u32_t {
  return OGLShaderProgramExtension::glCreateProgramObjectARB();
}

void OGLShaderProgramHelper::EMU_DeleteProgram([[maybe_unused]] s32_t num, [[maybe_unused]] const u32_t *programs) {}

void OGLShaderProgramHelper::STD_DeleteProgram([[maybe_unused]] s32_t num, const u32_t *programs) {
  glDeleteProgram(programs[0]);
}

void OGLShaderProgramHelper::ARB_DeleteProgram(s32_t num, const u32_t *programs) {
  OGLShaderProgramExtension::glDeleteProgramsARB(num, programs);
}

void OGLShaderProgramHelper::EMU_AttachShader(
    [[maybe_unused]] std::optional<u32_t> progId, [[maybe_unused]] std::optional<u32_t> shaderId) {}

void OGLShaderProgramHelper::STD_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId) {
  glAttachShader(progId.value(), shaderId.value());
}

void OGLShaderProgramHelper::ARB_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId) {
  OGLShaderProgramExtension::glAttachObjectARB(progId.value(), shaderId.value());
}

void OGLShaderProgramHelper::EMU_DetachShader(
    [[maybe_unused]] std::optional<u32_t> progId, [[maybe_unused]] std::optional<u32_t> shaderId) {}

void OGLShaderProgramHelper::STD_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId) {
  glDetachShader(progId.value(), shaderId.value());
}

void OGLShaderProgramHelper::ARB_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId) {
  OGLShaderProgramExtension::glDetachObjectARB(progId.value(), shaderId.value());
}

void OGLShaderProgramHelper::EMU_LinkProgram([[maybe_unused]] std::optional<u32_t> progId, s32_t *status) {}

void OGLShaderProgramHelper::STD_LinkProgram(std::optional<u32_t> progId, s32_t *status) {
  glLinkProgram(progId.value());
  glGetProgramiv(progId.value(), GL_LINK_STATUS, status);
}

void OGLShaderProgramHelper::ARB_LinkProgram(std::optional<u32_t> progId, s32_t *status) {
  OGLShaderProgramExtension::glLinkProgramARB(progId.value());
  OGLInfoHelper::ARB_getObjectParameter(progId.value(), GL_OBJECT_LINK_STATUS_ARB, status);
}

void OGLShaderProgramHelper::EMU_ValidateProgram(
    [[maybe_unused]] std::optional<u32_t> progId, [[maybe_unused]] s32_t *status) {}

void OGLShaderProgramHelper::STD_ValidateProgram(std::optional<u32_t> progId, s32_t *status) {
  glValidateProgram(progId.value());
  glGetProgramiv(progId.value(), GL_VALIDATE_STATUS, status);
}

void OGLShaderProgramHelper::ARB_ValidateProgram(std::optional<u32_t> progId, s32_t *status) {
  OGLShaderProgramExtension::glValidateProgramARB(progId.value());
  OGLInfoHelper::ARB_getObjectParameter(progId.value(), GL_OBJECT_VALIDATE_STATUS_ARB, status);
}

void OGLShaderProgramHelper::EMU_UseProgram([[maybe_unused]] std::optional<u32_t> progId) {}

void OGLShaderProgramHelper::STD_UseProgram(std::optional<u32_t> progId) { glUseProgram(progId.value()); }

void OGLShaderProgramHelper::ARB_UseProgram(std::optional<u32_t> progId) {
  OGLShaderProgramExtension::glUseProgramObjectARB(progId.value());
}

auto OGLShaderProgramHelper::EMU_getUniformLocation(
    [[maybe_unused]] std::optional<u32_t> progId, [[maybe_unused]] lpcstr_t name) -> s32_t {
  return 0;
}

auto OGLShaderProgramHelper::STD_getUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t {
  return glGetUniformLocation(progId.value(), name);
}

auto OGLShaderProgramHelper::ARB_getUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t {
  OGLShaderProgramExtension::glGetUniformLocationARB(progId.value(), name);
}

void OGLShaderProgramHelper::EMU_setUniform1i(s32_t loc, s32_t val) {}

void OGLShaderProgramHelper::STD_setUniform1i(s32_t loc, s32_t val) { glUniform1i(loc, val); }

void OGLShaderProgramHelper::ARB_setUniform1i(s32_t loc, s32_t val) {
  OGLShaderProgramExtension::glUniform1iARB(loc, val);
}

void OGLShaderProgramHelper::EMU_setUniform1f(s32_t loc, f32_t val) {}

void OGLShaderProgramHelper::STD_setUniform1f(s32_t loc, f32_t val) { glUniform1f(loc, val); }

void OGLShaderProgramHelper::ARB_setUniform1f(s32_t loc, f32_t val) {
  OGLShaderProgramExtension::glUniform1fARB(loc, val);
}

void OGLShaderProgramHelper::EMU_setUniform4f([[maybe_unused]] s32_t loc, [[maybe_unused]] f32_t v0,
    [[maybe_unused]] f32_t v1, [[maybe_unused]] f32_t v2, [[maybe_unused]] f32_t v3) {}

void OGLShaderProgramHelper::STD_setUniform4f(s32_t loc, f32_t v0, f32_t v1, f32_t v2, f32_t v3) {
  glUniform4f(loc, v0, v1, v2, v3);
}

void OGLShaderProgramHelper::ARB_setUniform4f(s32_t loc, f32_t v0, f32_t v1, f32_t v2, f32_t v3) {
  OGLShaderProgramExtension::glUniform4fARB(loc, v0, v1, v2, v3);
}

void OGLShaderProgramHelper::EMU_setUniformMatrix4f([[maybe_unused]] s32_t loc, [[maybe_unused]] s32_t count,
    [[maybe_unused]] bool transpose, [[maybe_unused]] const f32_t *val) {}

void OGLShaderProgramHelper::STD_setUniformMatrix4f(s32_t loc, s32_t count, bool transpose, const f32_t *val) {
  glUniformMatrix4fv(loc, count, transpose, val);
}

void OGLShaderProgramHelper::ARB_setUniformMatrix4f(s32_t loc, s32_t count, bool transpose, const f32_t *val) {
  OGLShaderProgramExtension::glUniformMatrix4fvARB(loc, count, transpose, val);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
