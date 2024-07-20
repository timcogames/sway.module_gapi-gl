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

  DECLARE_GENERIC_MEMBER(u32_t, OGLShaderProgramHelper, createProgram, /* ... */)
  auto EMU_CreateProgram() -> u32_t;
  auto STD_CreateProgram() -> u32_t;
  auto ARB_CreateProgram() -> u32_t;

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, deleteProgram, i32_t, const u32_t *)
  void EMU_DeleteProgram(i32_t num, const u32_t *progIds);
  void STD_DeleteProgram(i32_t num, const u32_t *progIds);
  void ARB_DeleteProgram(i32_t num, const u32_t *progIds);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, attachShader, std::optional<u32_t>, std::optional<u32_t>)
  void EMU_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void STD_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void ARB_AttachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, detachShader, std::optional<u32_t>, std::optional<u32_t>)
  void EMU_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void STD_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);
  void ARB_DetachShader(std::optional<u32_t> progId, std::optional<u32_t> shaderId);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, linkProgram, std::optional<u32_t>, i32_t *)
  void EMU_LinkProgram(std::optional<u32_t> progId, i32_t *status);
  void STD_LinkProgram(std::optional<u32_t> progId, i32_t *status);
  void ARB_LinkProgram(std::optional<u32_t> progId, i32_t *status);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, validateProgram, std::optional<u32_t>, i32_t *)
  void EMU_ValidateProgram(std::optional<u32_t> progId, i32_t *status);
  void STD_ValidateProgram(std::optional<u32_t> progId, i32_t *status);
  void ARB_ValidateProgram(std::optional<u32_t> progId, i32_t *status);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, useProgram, std::optional<u32_t>)
  void EMU_UseProgram(std::optional<u32_t> progId);
  void STD_UseProgram(std::optional<u32_t> progId);
  void ARB_UseProgram(std::optional<u32_t> progId);

  DECLARE_GENERIC_MEMBER(i32_t, OGLShaderProgramHelper, getUniformLocation, std::optional<u32_t>, lpcstr_t)
  auto EMU_GetUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> i32_t;
  auto STD_GetUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> i32_t;
  auto ARB_GetUniformLocation(std::optional<u32_t> progId, lpcstr_t name) -> i32_t;

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, setUniform1i, i32_t, i32_t)
  void EMU_SetUniform1i(i32_t loc, i32_t val);
  void STD_SetUniform1i(i32_t loc, i32_t val);
  void ARB_SetUniform1i(i32_t loc, i32_t val);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, setUniform1f, i32_t, f32_t)
  void EMU_SetUniform1f(i32_t loc, f32_t val);
  void STD_SetUniform1f(i32_t loc, f32_t val);
  void ARB_SetUniform1f(i32_t loc, f32_t val);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, setUniformVec4f, i32_t, math::vec4f_t)
  void EMU_SetUniformVec4f(i32_t loc, math::vec4f_t vec);
  void STD_SetUniformVec4f(i32_t loc, math::vec4f_t vec);
  void ARB_SetUniformVec4f(i32_t loc, math::vec4f_t vec);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, setUniformArr4f, i32_t, i32_t, f32_t *)
  void EMU_SetUniformArr4f(i32_t loc, i32_t count, f32_t *val);
  void STD_SetUniformArr4f(i32_t loc, i32_t count, f32_t *val);
  void ARB_SetUniformArr4f(i32_t loc, i32_t count, f32_t *val);

  DECLARE_GENERIC_MEMBER(void, OGLShaderProgramHelper, setUniformMatrix4f, i32_t, i32_t, bool, const f32_t *)
  void EMU_SetUniformMatrix4f(i32_t loc, i32_t count, bool transpose, const f32_t *val);
  void STD_SetUniformMatrix4f(i32_t loc, i32_t count, bool transpose, const f32_t *val);
  void ARB_SetUniformMatrix4f(i32_t loc, i32_t count, bool transpose, const f32_t *val);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLSHADERPROGRAMHELPER_HPP
