#ifndef SWAY_GAPI_GL_WRAP_OGLGENERICSHADERHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLGENERICSHADERHELPER_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>
#include <sway/gapi/gl/wrap/oglinfohelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLGenericShaderHelperIface {
public:
  virtual ~OGLGenericShaderHelperIface() = default;

  PURE_VIRTUAL(auto createShader(u32_t) -> u32_t);

  PURE_VIRTUAL(void deleteShader(std::optional<u32_t>));

  PURE_VIRTUAL(void shaderSource(std::optional<u32_t>, i32_t, lpcstr_t *, const i32_t *));

  PURE_VIRTUAL(void compileShader(std::optional<u32_t>, i32_t *));

  PURE_VIRTUAL(auto getAttribLocation(u32_t, lpcstr_t) -> i32_t);
};

class OGLGenericShaderHelper : public OGLGenericShaderHelperIface, public OGLInfoHelper {
public:
  OGLGenericShaderHelper();

  virtual ~OGLGenericShaderHelper() = default;

  // clang-format off
  DECLARE_GENERIC_CALLBACK_FUNC(u32_t, OGLGenericShaderHelper, createShader, u32_t)
  MTHD_VIRTUAL(auto createShader(u32_t type) -> u32_t { 
    return (this->*createShader_)(type); 
  });
  // clang-format on

  auto EMU_CreateShader(u32_t type) -> u32_t;
  auto STD_CreateShader(u32_t type) -> u32_t;
  auto ARB_CreateShader(u32_t type) -> u32_t;

  // clang-format off
  DECLARE_GENERIC_CALLBACK_FUNC(void, OGLGenericShaderHelper, deleteShader, std::optional<u32_t>)
  MTHD_VIRTUAL(void deleteShader(std::optional<u32_t> obj) { 
    return (this->*deleteShader_)(obj); 
  });
  // clang-format on

  void EMU_DeleteShader(std::optional<u32_t> obj);
  void STD_DeleteShader(std::optional<u32_t> obj);
  void ARB_DeleteShader(std::optional<u32_t> obj);

  // clang-format off
  DECLARE_GENERIC_CALLBACK_FUNC(void, OGLGenericShaderHelper, shaderSource, std::optional<u32_t>, i32_t, lpcstr_t *, const i32_t *)
  MTHD_VIRTUAL(void shaderSource(std::optional<u32_t> obj, i32_t count, lpcstr_t *str, const i32_t *len) {
    return (this->*shaderSource_)(obj, count, str, len);
  });
  // clang-format on

  void EMU_ShaderSource(std::optional<u32_t> obj, i32_t count, lpcstr_t *str, const i32_t *len);
  void STD_ShaderSource(std::optional<u32_t> obj, i32_t count, lpcstr_t *str, const i32_t *len);
  void ARB_ShaderSource(std::optional<u32_t> obj, i32_t count, lpcstr_t *str, const i32_t *len);

  // clang-format off
  DECLARE_GENERIC_CALLBACK_FUNC(void, OGLGenericShaderHelper, compileShader, std::optional<u32_t>, i32_t *)
  MTHD_VIRTUAL(void compileShader(std::optional<u32_t> obj, i32_t *status) { 
    return (this->*compileShader_)(obj, status); 
  });
  // clang-format on

  void EMU_CompileShader(std::optional<u32_t> obj, i32_t *status);
  void STD_CompileShader(std::optional<u32_t> obj, i32_t *status);
  void ARB_CompileShader(std::optional<u32_t> obj, i32_t *status);

  // clang-format off
  DECLARE_GENERIC_CALLBACK_FUNC(i32_t, OGLGenericShaderHelper, getAttribLocation, u32_t, lpcstr_t)
  MTHD_VIRTUAL(auto getAttribLocation(u32_t program, lpcstr_t name) -> i32_t { 
    return (this->*getAttribLocation_)(program, name);
  });
  // clang-format on

  auto EMU_GetAttribLocation(u32_t program, lpcstr_t name) -> i32_t;
  auto STD_GetAttribLocation(u32_t program, lpcstr_t name) -> i32_t;
  auto ARB_GetAttribLocation(u32_t program, lpcstr_t name) -> i32_t;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_WRAP_OGLGENERICSHADERHELPER_HPP
