#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramextension.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramhelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLShaderProgramHelper::OGLShaderProgramHelper() {
#ifdef _STUB
  createProgram_ = &OGLShaderProgramHelper::EMU_CreateProgram;
  deleteProgram_ = &OGLShaderProgramHelper::EMU_DeleteProgram;
  attachShader_ = &OGLShaderProgramHelper::EMU_AttachShader;
  detachShader_ = &OGLShaderProgramHelper::EMU_DetachShader;
  linkProgram_ = &OGLShaderProgramHelper::EMU_LinkProgram;
  validateProgram_ = &OGLShaderProgramHelper::EMU_ValidateProgram;
  useProgram_ = &OGLShaderProgramHelper::EMU_UseProgram;
  getUniformLocation_ = &OGLShaderProgramHelper::EMU_GetUniformLocation;
  setUniformVec4f_ = &OGLShaderProgramHelper::EMU_SetUniformVec4f;
  setUniformArr4f_ = &OGLShaderProgramHelper::EMU_SetUniformArr4f;
  setUniformMatrix4f_ = &OGLShaderProgramHelper::EMU_SetUniformMatrix4f;
  setUniform1i_ = &OGLShaderProgramHelper::EMU_SetUniform1i;
  setUniform1f_ = &OGLShaderProgramHelper::EMU_SetUniform1f;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_shader_objects")) {
    createProgram_ = &OGLShaderProgramHelper::ARB_CreateProgram;
    deleteProgram_ = &OGLShaderProgramHelper::ARB_DeleteProgram;
    attachShader_ = &OGLShaderProgramHelper::ARB_AttachShader;
    detachShader_ = &OGLShaderProgramHelper::ARB_DetachShader;
    linkProgram_ = &OGLShaderProgramHelper::ARB_LinkProgram;
    validateProgram_ = &OGLShaderProgramHelper::ARB_ValidateProgram;
    useProgram_ = &OGLShaderProgramHelper::ARB_UseProgram;
    getUniformLocation_ = &OGLShaderProgramHelper::ARB_GetUniformLocation;
    setUniformVec4f_ = &OGLShaderProgramHelper::ARB_SetUniformVec4f;
    setUniformArr4f_ = &OGLShaderProgramHelper::ARB_SetUniformArr4f;
    setUniformMatrix4f_ = &OGLShaderProgramHelper::ARB_SetUniformMatrix4f;
    setUniform1i_ = &OGLShaderProgramHelper::ARB_SetUniform1i;
    setUniform1f_ = &OGLShaderProgramHelper::ARB_SetUniform1f;
  } else {
    createProgram_ = &OGLShaderProgramHelper::STD_CreateProgram;
    deleteProgram_ = &OGLShaderProgramHelper::STD_DeleteProgram;
    attachShader_ = &OGLShaderProgramHelper::STD_AttachShader;
    detachShader_ = &OGLShaderProgramHelper::STD_DetachShader;
    linkProgram_ = &OGLShaderProgramHelper::STD_LinkProgram;
    validateProgram_ = &OGLShaderProgramHelper::STD_ValidateProgram;
    useProgram_ = &OGLShaderProgramHelper::STD_UseProgram;
    getUniformLocation_ = &OGLShaderProgramHelper::STD_GetUniformLocation;
    setUniformVec4f_ = &OGLShaderProgramHelper::STD_SetUniformVec4f;
    setUniformArr4f_ = &OGLShaderProgramHelper::STD_SetUniformArr4f;
    setUniformMatrix4f_ = &OGLShaderProgramHelper::STD_SetUniformMatrix4f;
    setUniform1i_ = &OGLShaderProgramHelper::STD_SetUniform1i;
    setUniform1f_ = &OGLShaderProgramHelper::STD_SetUniform1f;
  }

#endif
}

auto OGLShaderProgramHelper::EMU_CreateProgram() -> u32_t { return 0; }

auto OGLShaderProgramHelper::STD_CreateProgram() -> u32_t { return glCreateProgram(); }

auto OGLShaderProgramHelper::ARB_CreateProgram() -> u32_t {
  return OGLShaderProgramExtension::glCreateProgramObjectARB();
}

void OGLShaderProgramHelper::EMU_DeleteProgram([[maybe_unused]] i32_t num, [[maybe_unused]] const u32_t *programs) {}

void OGLShaderProgramHelper::STD_DeleteProgram([[maybe_unused]] i32_t num, const u32_t *programs) {
  glDeleteProgram(programs[0]);
}

void OGLShaderProgramHelper::ARB_DeleteProgram(i32_t num, const u32_t *programs) {
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

void OGLShaderProgramHelper::EMU_LinkProgram([[maybe_unused]] std::optional<u32_t> progId, i32_t *status) {}

void OGLShaderProgramHelper::STD_LinkProgram(std::optional<u32_t> progId, i32_t *status) {
  glLinkProgram(progId.value());
  glGetProgramiv(progId.value(), GL_LINK_STATUS, status);
}

void OGLShaderProgramHelper::ARB_LinkProgram(std::optional<u32_t> progId, i32_t *status) {
  OGLShaderProgramExtension::glLinkProgramARB(progId.value());
  OGLInfoHelper::ARB_GetObjectParameter(progId.value(), GL_OBJECT_LINK_STATUS_ARB, status);
}

void OGLShaderProgramHelper::EMU_ValidateProgram(
    [[maybe_unused]] std::optional<u32_t> progId, [[maybe_unused]] i32_t *status) {}

void OGLShaderProgramHelper::STD_ValidateProgram(std::optional<u32_t> progId, i32_t *status) {
  glValidateProgram(progId.value());
  glGetProgramiv(progId.value(), GL_VALIDATE_STATUS, status);
}

void OGLShaderProgramHelper::ARB_ValidateProgram(std::optional<u32_t> progId, i32_t *status) {
  OGLShaderProgramExtension::glValidateProgramARB(progId.value());
  OGLInfoHelper::ARB_GetObjectParameter(progId.value(), GL_OBJECT_VALIDATE_STATUS_ARB, status);
}

void OGLShaderProgramHelper::EMU_UseProgram([[maybe_unused]] std::optional<u32_t> progId) {}

void OGLShaderProgramHelper::STD_UseProgram(std::optional<u32_t> progId) { glUseProgram(progId.value()); }

void OGLShaderProgramHelper::ARB_UseProgram(std::optional<u32_t> progId) {
  OGLShaderProgramExtension::glUseProgramObjectARB(progId.value());
}

auto OGLShaderProgramHelper::EMU_GetUniformLocation(
    [[maybe_unused]] std::optional<u32_t> progId, [[maybe_unused]] lpcstr_t name) -> i32_t {
  return 0;
}

auto OGLShaderProgramHelper::STD_GetUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> i32_t {
  return glGetUniformLocation(progId.value(), name);
}

auto OGLShaderProgramHelper::ARB_GetUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> i32_t {
  return OGLShaderProgramExtension::glGetUniformLocationARB(progId.value(), name);
}

void OGLShaderProgramHelper::EMU_SetUniform1i(i32_t loc, i32_t val) {}

void OGLShaderProgramHelper::STD_SetUniform1i(i32_t loc, i32_t val) { glUniform1i(loc, val); }

void OGLShaderProgramHelper::ARB_SetUniform1i(i32_t loc, i32_t val) {
  OGLShaderProgramExtension::glUniform1iARB(loc, val);
}

void OGLShaderProgramHelper::EMU_SetUniform1f(i32_t loc, f32_t val) {}

void OGLShaderProgramHelper::STD_SetUniform1f(i32_t loc, f32_t val) { glUniform1f(loc, val); }

void OGLShaderProgramHelper::ARB_SetUniform1f(i32_t loc, f32_t val) {
  OGLShaderProgramExtension::glUniform1fARB(loc, val);
}

void OGLShaderProgramHelper::EMU_SetUniformVec4f([[maybe_unused]] i32_t loc, [[maybe_unused]] math::vec4f_t vec) {}

void OGLShaderProgramHelper::STD_SetUniformVec4f(i32_t loc, math::vec4f_t vec) {
  glUniform4f(loc, vec.getX(), vec.getY(), vec.getZ(), vec.getW());
}

void OGLShaderProgramHelper::ARB_SetUniformVec4f(i32_t loc, math::vec4f_t vec) {
  OGLShaderProgramExtension::glUniform4fARB(loc, vec.getX(), vec.getY(), vec.getZ(), vec.getW());
}

void OGLShaderProgramHelper::EMU_SetUniformArr4f(
    [[maybe_unused]] i32_t loc, [[maybe_unused]] i32_t count, [[maybe_unused]] f32_t *val) {}

void OGLShaderProgramHelper::STD_SetUniformArr4f(i32_t loc, i32_t count, f32_t *val) { glUniform4fv(loc, count, val); }

void OGLShaderProgramHelper::ARB_SetUniformArr4f(i32_t loc, i32_t count, f32_t *val) {
  OGLShaderProgramExtension::glUniform4fvARB(loc, count, val);
}

void OGLShaderProgramHelper::EMU_SetUniformMatrix4f([[maybe_unused]] i32_t loc, [[maybe_unused]] i32_t count,
    [[maybe_unused]] bool transpose, [[maybe_unused]] const f32_t *val) {}

void OGLShaderProgramHelper::STD_SetUniformMatrix4f(i32_t loc, i32_t count, bool transpose, const f32_t *val) {
  glUniformMatrix4fv(loc, count, transpose, val);
}

void OGLShaderProgramHelper::ARB_SetUniformMatrix4f(i32_t loc, i32_t count, bool transpose, const f32_t *val) {
  OGLShaderProgramExtension::glUniformMatrix4fvARB(loc, count, transpose, val);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
