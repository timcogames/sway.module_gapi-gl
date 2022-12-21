#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/oglgenericshaderhelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLGenericShaderHelper::OGLGenericShaderHelper(std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> exts)
    : extensions_(std::move(exts)) {

#ifdef _STUB
  CreateShader_ = &OGLGenericShaderHelper::EMU_CreateShader;
  DeleteShader_ = &OGLGenericShaderHelper::EMU_DeleteShader;
  ShaderSource_ = &OGLGenericShaderHelper::EMU_ShaderSource;
  CompileShader_ = &OGLGenericShaderHelper::EMU_CompileShader;
  GetShaderParam_ = &OGLGenericShaderHelper::EMU_GetShaderParam;
  GetAttribLocation_ = &OGLGenericShaderHelper::EMU_GetAttribLocation;
#else

  const auto *extensions = OGLCapability::getExtensions();

  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_shader_objects")) {
    CreateShader_ = &OGLGenericShaderHelper::ARB_CreateShader;
    DeleteShader_ = &OGLGenericShaderHelper::ARB_DeleteShader;
    ShaderSource_ = &OGLGenericShaderHelper::ARB_ShaderSource;
    CompileShader_ = &OGLGenericShaderHelper::ARB_CompileShader;
    GetShaderParam_ = &OGLGenericShaderHelper::ARB_GetShaderParam;
  } else {
    CreateShader_ = &OGLGenericShaderHelper::STD_CreateShader;
    DeleteShader_ = &OGLGenericShaderHelper::STD_DeleteShader;
    ShaderSource_ = &OGLGenericShaderHelper::STD_ShaderSource;
    CompileShader_ = &OGLGenericShaderHelper::STD_CompileShader;
    GetShaderParam_ = &OGLGenericShaderHelper::STD_GetShaderParam;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_vertex_shader")) {
    GetAttribLocation_ = &OGLGenericShaderHelper::ARB_GetAttribLocation;
  } else {
    GetAttribLocation_ = &OGLGenericShaderHelper::STD_GetAttribLocation;
  }

#endif
}

auto OGLGenericShaderHelper::EMU_CreateShader([[maybe_unused]] u32_t type) -> u32_t { return 0; }

auto OGLGenericShaderHelper::STD_CreateShader(u32_t type) -> u32_t { return glCreateShader(type); }

auto OGLGenericShaderHelper::ARB_CreateShader(u32_t type) -> u32_t {
  // core::binding::TFunction<u32_t(u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glCreateShaderObjectARB"}});

  // return callbackFunc(type);

  return Extension::glCreateShaderObject(type);
}

void OGLGenericShaderHelper::EMU_DeleteShader([[maybe_unused]] std::optional<u32_t> obj) {}

void OGLGenericShaderHelper::STD_DeleteShader(std::optional<u32_t> obj) { glDeleteShader(obj.value()); }

void OGLGenericShaderHelper::ARB_DeleteShader(std::optional<u32_t> obj) {
  // core::binding::TFunction<void(std::optional<u32_t>)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glDeleteObjectARB"}});

  // callbackFunc(obj.value());

  Extension::glDeleteShaderObject(obj.value());
}

void OGLGenericShaderHelper::EMU_ShaderSource([[maybe_unused]] std::optional<u32_t> obj, [[maybe_unused]] s32_t count,
    [[maybe_unused]] lpcstr_t *string, [[maybe_unused]] const s32_t *length) {}

void OGLGenericShaderHelper::STD_ShaderSource(
    std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length) {
  glShaderSource(obj.value(), count, string, length);
}

void OGLGenericShaderHelper::ARB_ShaderSource(
    std::optional<u32_t> obj, s32_t count, lpcstr_t *string, const s32_t *length) {
  // core::binding::TFunction<void(std::optional<u32_t>, s32_t, lpcstr_t *, const s32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glShaderSourceARB"}});

  // callbackFunc(obj.value(), count, string, length);

  Extension::glShaderSource(obj.value(), count, string, length);
}

void OGLGenericShaderHelper::EMU_CompileShader([[maybe_unused]] std::optional<u32_t> obj) {}

void OGLGenericShaderHelper::STD_CompileShader(std::optional<u32_t> obj) { glCompileShader(obj.value()); }

void OGLGenericShaderHelper::ARB_CompileShader(std::optional<u32_t> obj) {
  // core::binding::TFunction<void(std::optional<u32_t>)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glCompileShaderARB"}});

  // callbackFunc(obj.value());

  Extension::glCompileShader(obj.value());
}

void OGLGenericShaderHelper::EMU_GetShaderParam(
    [[maybe_unused]] std::optional<u32_t> obj, [[maybe_unused]] u32_t pname, [[maybe_unused]] s32_t *params) {}

void OGLGenericShaderHelper::STD_GetShaderParam(std::optional<u32_t> obj, u32_t pname, s32_t *params) {
  glGetShaderiv(obj.value(), pname, params);
}

void OGLGenericShaderHelper::ARB_GetShaderParam(std::optional<u32_t> obj, u32_t pname, s32_t *params) {
  // core::binding::TFunction<void(std::optional<u32_t>, u32_t, s32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_shader_objects", "glGetObjectParameterivARB"}});

  // callbackFunc(obj.value(), pname, params);

  Extension::glGetObjectParameteriv(obj.value(), pname, params);
}

auto OGLGenericShaderHelper::EMU_GetAttribLocation([[maybe_unused]] u32_t program, [[maybe_unused]] lpcstr_t name)
    -> s32_t {
  return 0;
}

auto OGLGenericShaderHelper::STD_GetAttribLocation(u32_t program, lpcstr_t name) -> s32_t {
  return glGetAttribLocation(program, name);
}

auto OGLGenericShaderHelper::ARB_GetAttribLocation(u32_t program, lpcstr_t name) -> s32_t {
  // core::binding::TFunction<u32_t(u32_t, lpcstr_t)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_shader", "glGetAttribLocationARB"}});

  // return callbackFunc(program, name);

  return Extension::glGetAttribLocation(program, name);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
