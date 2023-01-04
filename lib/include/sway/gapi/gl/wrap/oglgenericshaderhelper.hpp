#ifndef SWAY_GAPI_GL_WRAP_OGLGENERICSHADERHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLGENERICSHADERHELPER_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>
#include <sway/gapi/gl/wrap/oglinfohelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLGenericShaderHelper : public OGLInfoHelper {
public:
  OGLGenericShaderHelper();

  DECLARE_GENERIC_MEMBER(u32_t, OGLGenericShaderHelper, CreateShader, u32_t)
  auto EMU_CreateShader(u32_t type) -> u32_t;
  auto STD_CreateShader(u32_t type) -> u32_t;
  auto ARB_CreateShader(u32_t type) -> u32_t;

  DECLARE_GENERIC_MEMBER(void, OGLGenericShaderHelper, DeleteShader, std::optional<u32_t>)
  void EMU_DeleteShader(std::optional<u32_t> obj);
  void STD_DeleteShader(std::optional<u32_t> obj);
  void ARB_DeleteShader(std::optional<u32_t> obj);

  DECLARE_GENERIC_MEMBER(
      void, OGLGenericShaderHelper, ShaderSource, std::optional<u32_t>, s32_t, lpcstr_t *, const s32_t *)
  void EMU_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length);
  void STD_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length);
  void ARB_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length);

  DECLARE_GENERIC_MEMBER(void, OGLGenericShaderHelper, CompileShader, std::optional<u32_t>, s32_t *)
  void EMU_CompileShader(std::optional<u32_t> obj, s32_t *status);
  void STD_CompileShader(std::optional<u32_t> obj, s32_t *status);
  void ARB_CompileShader(std::optional<u32_t> obj, s32_t *status);

  DECLARE_GENERIC_MEMBER(s32_t, OGLGenericShaderHelper, getAttribLocation, u32_t, lpcstr_t)
  auto EMU_getAttribLocation(u32_t program, lpcstr_t name) -> s32_t;
  auto STD_getAttribLocation(u32_t program, lpcstr_t name) -> s32_t;
  auto ARB_getAttribLocation(u32_t program, lpcstr_t name) -> s32_t;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLGENERICSHADERHELPER_HPP
