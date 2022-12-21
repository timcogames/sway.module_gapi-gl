#ifndef SWAY_GAPI_GL_OGLGENERICSHADERHELPER_HPP
#define SWAY_GAPI_GL_OGLGENERICSHADERHELPER_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrapset/genericmembermacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLGenericShaderHelper {
public:
  OGLGenericShaderHelper(std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> exts);

  DECLARE_GENERIC_MEMBER(OGLGenericShaderHelper, CreateShader, u32_t, u32_t)
  auto EMU_CreateShader(u32_t type) -> u32_t;
  auto STD_CreateShader(u32_t type) -> u32_t;
  auto ARB_CreateShader(u32_t type) -> u32_t;

  DECLARE_GENERIC_MEMBER(OGLGenericShaderHelper, DeleteShader, void, std::optional<u32_t>)
  void EMU_DeleteShader(std::optional<u32_t> obj);
  void STD_DeleteShader(std::optional<u32_t> obj);
  void ARB_DeleteShader(std::optional<u32_t> obj);

  DECLARE_GENERIC_MEMBER(
      OGLGenericShaderHelper, ShaderSource, void, std::optional<u32_t>, s32_t, lpcstr_t *, const s32_t *)
  void EMU_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length);
  void STD_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length);
  void ARB_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length);

  DECLARE_GENERIC_MEMBER(OGLGenericShaderHelper, CompileShader, void, std::optional<u32_t>)
  void EMU_CompileShader(std::optional<u32_t> obj);
  void STD_CompileShader(std::optional<u32_t> obj);
  void ARB_CompileShader(std::optional<u32_t> obj);

  DECLARE_GENERIC_MEMBER(OGLGenericShaderHelper, GetShaderParam, void, std::optional<u32_t>, u32_t, s32_t *)
  void EMU_GetShaderParam(std::optional<u32_t> obj, u32_t pname, s32_t *params);
  void STD_GetShaderParam(std::optional<u32_t> obj, u32_t pname, s32_t *params);
  void ARB_GetShaderParam(std::optional<u32_t> obj, u32_t pname, s32_t *params);

  DECLARE_GENERIC_MEMBER(OGLGenericShaderHelper, GetAttribLocation, s32_t, u32_t, lpcstr_t)
  auto EMU_GetAttribLocation(u32_t program, lpcstr_t name) -> s32_t;
  auto STD_GetAttribLocation(u32_t program, lpcstr_t name) -> s32_t;
  auto ARB_GetAttribLocation(u32_t program, lpcstr_t name) -> s32_t;

private:
  std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> extensions_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLGENERICSHADERHELPER_HPP
