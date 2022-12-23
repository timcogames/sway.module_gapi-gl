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

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, AttachShader, void, std::optional<u32_t>, std::optional<u32_t>)
  void EMU_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void STD_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void ARB_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, DetachShader, void, std::optional<u32_t>, std::optional<u32_t>)
  void EMU_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void STD_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void ARB_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, LinkProgram, void, std::optional<u32_t>, s32_t *)
  void EMU_LinkProgram(std::optional<u32_t> progId, s32_t *status);
  void STD_LinkProgram(std::optional<u32_t> progId, s32_t *status);
  void ARB_LinkProgram(std::optional<u32_t> progId, s32_t *status);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, ValidateProgram, void, std::optional<u32_t>, s32_t *)
  void EMU_ValidateProgram(std::optional<u32_t> progId, s32_t *status);
  void STD_ValidateProgram(std::optional<u32_t> progId, s32_t *status);
  void ARB_ValidateProgram(std::optional<u32_t> progId, s32_t *status);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, UseProgram, void, std::optional<u32_t>)
  void EMU_UseProgram(std::optional<u32_t> progId);
  void STD_UseProgram(std::optional<u32_t> progId);
  void ARB_UseProgram(std::optional<u32_t> progId);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, GetUniformLocation, s32_t, std::optional<u32_t>, lpcstr_t)
  auto EMU_GetUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t;
  auto STD_GetUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t;
  auto ARB_GetUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t;

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, Uniform4f, void, s32_t, f32_t, f32_t, f32_t, f32_t)
  void EMU_Uniform4f(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3);
  void STD_Uniform4f(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3);
  void ARB_Uniform4f(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3);

  DECLARE_GENERIC_MEMBER(OGLShaderProgramHelper, UniformMatrix4f, void, s32_t, s32_t, bool, const f32_t *)
  void EMU_UniformMatrix4f(s32_t location, s32_t count, bool transpose, const f32_t *value);
  void STD_UniformMatrix4f(s32_t location, s32_t count, bool transpose, const f32_t *value);
  void ARB_UniformMatrix4f(s32_t location, s32_t count, bool transpose, const f32_t *value);

private:
  std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> extensions_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSHADERPROGRAMHELPER_HPP
