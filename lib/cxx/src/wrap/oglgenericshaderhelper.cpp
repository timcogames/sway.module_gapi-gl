#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglgenericshaderextension.hpp>
#include <sway/gapi/gl/wrap/oglgenericshaderhelper.hpp>

#include <GLES2/gl2.h>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

OGLGenericShaderHelper::OGLGenericShaderHelper() {
#ifdef _STUB
  createShader_ = &OGLGenericShaderHelper::EMU_CreateShader;
  deleteShader_ = &OGLGenericShaderHelper::EMU_DeleteShader;
  shaderSource_ = &OGLGenericShaderHelper::EMU_ShaderSource;
  compileShader_ = &OGLGenericShaderHelper::EMU_CompileShader;
  getAttribLocation_ = &OGLGenericShaderHelper::EMU_GetAttribLocation;
#else

  const auto *extensions = OGLCapability::getExtensions();

  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_shader_objects")) {
    createShader_ = &OGLGenericShaderHelper::ARB_CreateShader;
    deleteShader_ = &OGLGenericShaderHelper::ARB_DeleteShader;
    shaderSource_ = &OGLGenericShaderHelper::ARB_ShaderSource;
    compileShader_ = &OGLGenericShaderHelper::ARB_CompileShader;
  } else {
    createShader_ = &OGLGenericShaderHelper::STD_CreateShader;
    deleteShader_ = &OGLGenericShaderHelper::STD_DeleteShader;
    shaderSource_ = &OGLGenericShaderHelper::STD_ShaderSource;
    compileShader_ = &OGLGenericShaderHelper::STD_CompileShader;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_vertex_shader")) {
    getAttribLocation_ = &OGLGenericShaderHelper::ARB_GetAttribLocation;
  } else {
    getAttribLocation_ = &OGLGenericShaderHelper::STD_GetAttribLocation;
  }

#endif
}

auto OGLGenericShaderHelper::EMU_CreateShader([[maybe_unused]] u32_t type) -> u32_t { return 0; }

auto OGLGenericShaderHelper::STD_CreateShader(u32_t type) -> u32_t { return glCreateShader(type); }

auto OGLGenericShaderHelper::ARB_CreateShader(u32_t type) -> u32_t {
  return OGLGenericShaderExtension::glCreateShaderObjectARB(type);
}

void OGLGenericShaderHelper::EMU_DeleteShader([[maybe_unused]] std::optional<u32_t> obj) {}

void OGLGenericShaderHelper::STD_DeleteShader(std::optional<u32_t> obj) { glDeleteShader(obj.value()); }

void OGLGenericShaderHelper::ARB_DeleteShader(std::optional<u32_t> obj) {
  OGLGenericShaderExtension::glDeleteObjectARB(obj.value());
}

void OGLGenericShaderHelper::EMU_ShaderSource([[maybe_unused]] std::optional<u32_t> obj, [[maybe_unused]] i32_t count,
    [[maybe_unused]] lpcstr_t *str, [[maybe_unused]] const i32_t *len) {}

void OGLGenericShaderHelper::STD_ShaderSource(std::optional<u32_t> obj, i32_t count, lpcstr_t *str, const i32_t *len) {
  glShaderSource(obj.value(), count, str, len);
}

void OGLGenericShaderHelper::ARB_ShaderSource(std::optional<u32_t> obj, i32_t count, lpcstr_t *str, const i32_t *len) {
  OGLGenericShaderExtension::glShaderSourceARB(obj.value(), count, str, len);
}

void OGLGenericShaderHelper::EMU_CompileShader(
    [[maybe_unused]] std::optional<u32_t> obj, [[maybe_unused]] i32_t *status) {}

void OGLGenericShaderHelper::STD_CompileShader(std::optional<u32_t> obj, i32_t *status) {
  glCompileShader(obj.value());
  glGetShaderiv(obj.value(), GL_COMPILE_STATUS, status);
}

void OGLGenericShaderHelper::ARB_CompileShader(std::optional<u32_t> obj, i32_t *status) {
  OGLGenericShaderExtension::glCompileShaderARB(obj.value());
  OGLInfoHelper::ARB_GetObjectParameter(obj.value(), GL_OBJECT_COMPILE_STATUS_ARB, status);
}

auto OGLGenericShaderHelper::EMU_GetAttribLocation(
    [[maybe_unused]] u32_t program, [[maybe_unused]] lpcstr_t name) -> i32_t {
  return 0;
}

auto OGLGenericShaderHelper::STD_GetAttribLocation(u32_t program, lpcstr_t name) -> i32_t {
  return glGetAttribLocation(program, name);
}

auto OGLGenericShaderHelper::ARB_GetAttribLocation(u32_t program, lpcstr_t name) -> i32_t {
  return OGLGenericShaderExtension::glGetAttribLocationARB(program, name);
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
