#ifndef SWAY_GAPI_GL_OGLSHADERPROGRAMHELPER_HPP
#define SWAY_GAPI_GL_OGLSHADERPROGRAMHELPER_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrapset/genericmembermacros.hpp>

#include <variant>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLShaderProgramHelper {
public:
  OGLShaderProgramHelper(std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> exts);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, CreateProgram, u32_t, /* ... */)
  auto EMU_CreateProgram() -> u32_t;
  auto STD_CreateProgram() -> u32_t;
  auto ARB_CreateProgram() -> u32_t;

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, DeleteProgram, void, s32_t, const u32_t *)
  void EMU_DeleteProgram(s32_t num, const u32_t *programs);
  void STD_DeleteProgram(s32_t num, const u32_t *programs);
  void ARB_DeleteProgram(s32_t num, const u32_t *programs);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, AttachShader, void, u32_t, u32_t)
  void EMU_AttachShader(u32_t program, u32_t shader);
  void STD_AttachShader(u32_t program, u32_t shader);
  void ARB_AttachShader(u32_t program, u32_t shader);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, DetachShader, void, u32_t, u32_t)
  void EMU_DetachShader(u32_t program, u32_t shader);
  void STD_DetachShader(u32_t program, u32_t shader);
  void ARB_DetachShader(u32_t program, u32_t shader);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, LinkProgram, void, u32_t)
  void EMU_LinkProgram(u32_t program);
  void STD_LinkProgram(u32_t program);
  void ARB_LinkProgram(u32_t program);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, ValidateProgram, void, u32_t)
  void EMU_ValidateProgram(u32_t program);
  void STD_ValidateProgram(u32_t program);
  void ARB_ValidateProgram(u32_t program);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, UseProgram, void, u32_t)
  void EMU_UseProgram(u32_t program);
  void STD_UseProgram(u32_t program);
  void ARB_UseProgram(u32_t program);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, GetUniformLocation, s32_t, u32_t, lpcstr_t)
  auto EMU_GetUniformLocation(u32_t program, lpcstr_t name) -> s32_t;
  auto STD_GetUniformLocation(u32_t program, lpcstr_t name) -> s32_t;
  auto ARB_GetUniformLocation(u32_t program, lpcstr_t name) -> s32_t;

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, Uniform4f, void, s32_t, f32_t, f32_t, f32_t, f32_t)
  void EMU_Uniform4f(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3);
  void STD_Uniform4f(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3);
  void ARB_Uniform4f(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, UniformMatrix4f, void, s32_t, s32_t, bool, const f32_t *)
  void EMU_UniformMatrix4f(s32_t location, s32_t count, bool transpose, const f32_t *value);
  void STD_UniformMatrix4f(s32_t location, s32_t count, bool transpose, const f32_t *value);
  void ARB_UniformMatrix4f(s32_t location, s32_t count, bool transpose, const f32_t *value);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, GetObjectParam, void, u32_t, u32_t, s32_t *)
  void EMU_GetObjectParam(u32_t obj, u32_t pname, s32_t *params);
  void STD_GetObjectParam(u32_t obj, u32_t pname, s32_t *params);
  void ARB_GetObjectParam(u32_t obj, u32_t pname, s32_t *params);

private:
  std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> extensions_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSHADERPROGRAMHELPER_HPP
