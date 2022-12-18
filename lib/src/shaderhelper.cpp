#include <sway/gapi/gl/capability.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/shaderhelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

ShaderHelper::ShaderHelper(std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> exts)
    : extensions_(std::move(exts)) {

#ifdef _STUB
  CreateShader_ = &ShaderHelper::EMU_CreateShader;
  DeleteShader_ = &ShaderHelper::EMU_DeleteShader;
  ShaderSource_ = &ShaderHelper::EMU_ShaderSource;
  CompileShader_ = &ShaderHelper::EMU_CompileShader;
  GetShaderParam_ = &ShaderHelper::EMU_GetShaderParam;
  GetAttribLocation_ = &ShaderHelper::EMU_GetAttribLocation;
#else

  const auto *extensions = Capability::getExtensions();

  if (Capability::isExtensionSupported(extensions, "GL_ARB_shader_objects")) {
    CreateShader_ = &ShaderHelper::ARB_CreateShader;
    DeleteShader_ = &ShaderHelper::ARB_DeleteShader;
    ShaderSource_ = &ShaderHelper::ARB_ShaderSource;
    CompileShader_ = &ShaderHelper::ARB_CompileShader;
    GetShaderParam_ = &ShaderHelper::ARB_GetShaderParam;
  } else {
    CreateShader_ = &ShaderHelper::STD_CreateShader;
    DeleteShader_ = &ShaderHelper::STD_DeleteShader;
    ShaderSource_ = &ShaderHelper::STD_ShaderSource;
    CompileShader_ = &ShaderHelper::STD_CompileShader;
    GetShaderParam_ = &ShaderHelper::STD_GetShaderParam;
  }

  if (Capability::isExtensionSupported(extensions, "GL_ARB_vertex_shader")) {
    GetAttribLocation_ = &ShaderHelper::ARB_GetAttribLocation;
  } else {
    GetAttribLocation_ = &ShaderHelper::STD_GetAttribLocation;
  }

#endif
}

auto ShaderHelper::EMU_CreateShader([[maybe_unused]] u32_t type) -> u32_t { return 0; }

auto ShaderHelper::STD_CreateShader(u32_t type) -> u32_t { return glCreateShader(type); }

auto ShaderHelper::ARB_CreateShader(u32_t type) -> u32_t {
  // core::binding::TFunction<u32_t(u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glCreateShaderObjectARB"}});

  // return callbackFunc(type);

  return Extension::glCreateShaderObject(type);
}

void ShaderHelper::EMU_DeleteShader([[maybe_unused]] std::optional<u32_t> obj) {}

void ShaderHelper::STD_DeleteShader(std::optional<u32_t> obj) { glDeleteShader(obj.value()); }

void ShaderHelper::ARB_DeleteShader(std::optional<u32_t> obj) {
  // core::binding::TFunction<void(std::optional<u32_t>)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glDeleteObjectARB"}});

  // callbackFunc(obj.value());

  Extension::glDeleteShaderObject(obj.value());
}

void ShaderHelper::EMU_ShaderSource([[maybe_unused]] std::optional<u32_t> obj, [[maybe_unused]] s32_t count,
    [[maybe_unused]] lpcstr_t *string, [[maybe_unused]] const s32_t *length) {}

void ShaderHelper::STD_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length) {
  glShaderSource(obj.value(), count, string, length);
}

void ShaderHelper::ARB_ShaderSource(std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length) {
  // core::binding::TFunction<void(std::optional<u32_t>, s32_t, lpcstr_t *, const s32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glShaderSourceARB"}});

  // callbackFunc(obj.value(), count, string, length);

  Extension::glShaderSource(obj.value(), count, string, length);
}

void ShaderHelper::EMU_CompileShader([[maybe_unused]] std::optional<u32_t> obj) {}

void ShaderHelper::STD_CompileShader(std::optional<u32_t> obj) { glCompileShader(obj.value()); }

void ShaderHelper::ARB_CompileShader(std::optional<u32_t> obj) {
  // core::binding::TFunction<void(std::optional<u32_t>)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glCompileShaderARB"}});

  // callbackFunc(obj.value());

  Extension::glCompileShader(obj.value());
}

void ShaderHelper::EMU_GetShaderParam(
    [[maybe_unused]] std::optional<u32_t> obj, [[maybe_unused]] u32_t pname, [[maybe_unused]] s32_t *params) {}

void ShaderHelper::STD_GetShaderParam(std::optional<u32_t> obj, u32_t pname, s32_t *params) {
  glGetShaderiv(obj.value(), pname, params);
}

void ShaderHelper::ARB_GetShaderParam(std::optional<u32_t> obj, u32_t pname, s32_t *params) {
  // core::binding::TFunction<void(std::optional<u32_t>, u32_t, s32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glGetObjectParameterivARB"}});

  // callbackFunc(obj.value(), pname, params);

  Extension::glGetObjectParameteriv(obj.value(), pname, params);
}

auto ShaderHelper::EMU_GetAttribLocation([[maybe_unused]] u32_t program, [[maybe_unused]] lpcstr_t name) -> s32_t {
  return 0;
}

auto ShaderHelper::STD_GetAttribLocation(u32_t program, lpcstr_t name) -> s32_t {
  return glGetAttribLocation(program, name);
}

auto ShaderHelper::ARB_GetAttribLocation(u32_t program, lpcstr_t name) -> s32_t {
  // core::binding::TFunction<u32_t(u32_t, lpcstr_t)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_shader", "glGetAttribLocationARB"}});

  // return callbackFunc(program, name);

  return Extension::glGetAttribLocation(program, name);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
