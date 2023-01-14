#ifndef SWAY_GAPI_GL_WRAP_OGLSHADERPROGRAMHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLSHADERPROGRAMHELPER_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>
#include <sway/gapi/gl/wrap/oglinfohelper.hpp>

#include <variant>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLShaderProgramHelper : public OGLInfoHelper {
public:
  OGLShaderProgramHelper();

  DECLARE_GENERIC_MEMBER(u32_t, OGLShaderProgramHelper, CreateProgram, /* ... */)
  auto EMU_CreateProgram() -> u32_t;
  auto STD_CreateProgram() -> u32_t;
  auto ARB_CreateProgram() -> u32_t;

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, DeleteProgram, s32_t, const u32_t *)
  void EMU_DeleteProgram(s32_t num, const u32_t *progIds);
  void STD_DeleteProgram(s32_t num, const u32_t *progIds);
  void ARB_DeleteProgram(s32_t num, const u32_t *progIds);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, AttachShader, std::optional<u32_t>, std::optional<u32_t>)
  void EMU_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void STD_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void ARB_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, DetachShader, std::optional<u32_t>, std::optional<u32_t>)
  void EMU_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void STD_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void ARB_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, LinkProgram, std::optional<u32_t>, s32_t *)
  void EMU_LinkProgram(std::optional<u32_t> progId, s32_t *status);
  void STD_LinkProgram(std::optional<u32_t> progId, s32_t *status);
  void ARB_LinkProgram(std::optional<u32_t> progId, s32_t *status);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, ValidateProgram, std::optional<u32_t>, s32_t *)
  void EMU_ValidateProgram(std::optional<u32_t> progId, s32_t *status);
  void STD_ValidateProgram(std::optional<u32_t> progId, s32_t *status);
  void ARB_ValidateProgram(std::optional<u32_t> progId, s32_t *status);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, UseProgram, std::optional<u32_t>)
  void EMU_UseProgram(std::optional<u32_t> progId);
  void STD_UseProgram(std::optional<u32_t> progId);
  void ARB_UseProgram(std::optional<u32_t> progId);

  DECLARE_GENERIC_MEMBER(s32_t, OGLShaderProgramHelper, getUniformLocation, std::optional<u32_t>, lpcstr_t)
  auto EMU_getUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t;
  auto STD_getUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t;
  auto ARB_getUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t;

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, setUniform1i, s32_t, s32_t)
  void EMU_setUniform1i(s32_t loc, s32_t val);
  void STD_setUniform1i(s32_t loc, s32_t val);
  void ARB_setUniform1i(s32_t loc, s32_t val);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, setUniform1f, s32_t, f32_t)
  void EMU_setUniform1f(s32_t loc, f32_t val);
  void STD_setUniform1f(s32_t loc, f32_t val);
  void ARB_setUniform1f(s32_t loc, f32_t val);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, setUniform4f, s32_t, f32_t, f32_t, f32_t, f32_t)
  void EMU_setUniform4f(s32_t loc, f32_t v0, f32_t v1, f32_t v2, f32_t v3);
  void STD_setUniform4f(s32_t loc, f32_t v0, f32_t v1, f32_t v2, f32_t v3);
  void ARB_setUniform4f(s32_t loc, f32_t v0, f32_t v1, f32_t v2, f32_t v3);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, setUniformMatrix4f, s32_t, s32_t, bool, const f32_t *)
  void EMU_setUniformMatrix4f(s32_t loc, s32_t count, bool transpose, const f32_t *val);
  void STD_setUniformMatrix4f(s32_t loc, s32_t count, bool transpose, const f32_t *val);
  void ARB_setUniformMatrix4f(s32_t loc, s32_t count, bool transpose, const f32_t *val);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLSHADERPROGRAMHELPER_HPP
