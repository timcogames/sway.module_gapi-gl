#ifndef SWAY_GAPI_GL_WRAP_OGLGENERICSHADERHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLGENERICSHADERHELPER_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>
#include <sway/gapi/gl/wrap/oglinfohelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLGenericShaderHelperIface {
public:
  virtual ~OGLGenericShaderHelperIface() = default;

  // clang-format off
  PURE_VIRTUAL(auto createShader(u32_t) -> u32_t);  // clang-format on

  PURE_VIRTUAL(void deleteShader(std::optional<u32_t>));

  PURE_VIRTUAL(void shaderSource(std::optional<u32_t>, s32_t, lpcstr_t *, const s32_t *));

  PURE_VIRTUAL(void compileShader(std::optional<u32_t>, s32_t *));

  // clang-format off
  PURE_VIRTUAL(auto getAttribLocation(u32_t, lpcstr_t) -> s32_t);  // clang-format on
};

class OGLGenericShaderHelper : public OGLGenericShaderHelperIface, public OGLInfoHelper {
public:
  OGLGenericShaderHelper();

  virtual ~OGLGenericShaderHelper() = default;

  DECL_GENERIC_CALLBACK_FUNC(u32_t, OGLGenericShaderHelper, createShader, u32_t)
  // clang-format off
  MTHD_VIRTUAL(auto createShader(u32_t type) -> u32_t { return (this->*createShader_)(type); });  // clang-format on

  auto EMU_CreateShader(u32_t type) -> u32_t;
  auto STD_CreateShader(u32_t type) -> u32_t;
  auto ARB_CreateShader(u32_t type) -> u32_t;

  DECL_GENERIC_CALLBACK_FUNC(void, OGLGenericShaderHelper, deleteShader, std::optional<u32_t>)
  MTHD_VIRTUAL(void deleteShader(std::optional<u32_t> obj) { return (this->*deleteShader_)(obj); });

  void EMU_DeleteShader(std::optional<u32_t> obj);
  void STD_DeleteShader(std::optional<u32_t> obj);
  void ARB_DeleteShader(std::optional<u32_t> obj);

  DECL_GENERIC_CALLBACK_FUNC(
      void, OGLGenericShaderHelper, shaderSource, std::optional<u32_t>, s32_t, lpcstr_t *, const s32_t *)
  MTHD_VIRTUAL(void shaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length) {
    return (this->*shaderSource_)(obj, count, string, length);
  });

  void EMU_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length);
  void STD_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length);
  void ARB_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length);

  DECL_GENERIC_CALLBACK_FUNC(void, OGLGenericShaderHelper, compileShader, std::optional<u32_t>, s32_t *)
  MTHD_VIRTUAL(
      void compileShader(std::optional<u32_t> obj, s32_t *status) { return (this->*compileShader_)(obj, status); });

  void EMU_CompileShader(std::optional<u32_t> obj, s32_t *status);
  void STD_CompileShader(std::optional<u32_t> obj, s32_t *status);
  void ARB_CompileShader(std::optional<u32_t> obj, s32_t *status);

  DECL_GENERIC_CALLBACK_FUNC(s32_t, OGLGenericShaderHelper, getAttribLocation, u32_t, lpcstr_t)
  // clang-format off
  MTHD_VIRTUAL(auto getAttribLocation(u32_t program, lpcstr_t name) -> s32_t {  // clang-format on
    return (this->*getAttribLocation_)(program, name);
  });

  auto EMU_GetAttribLocation(u32_t program, lpcstr_t name) -> s32_t;
  auto STD_GetAttribLocation(u32_t program, lpcstr_t name) -> s32_t;
  auto ARB_GetAttribLocation(u32_t program, lpcstr_t name) -> s32_t;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLGENERICSHADERHELPER_HPP
