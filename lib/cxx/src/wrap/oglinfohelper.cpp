#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglinfoextension.hpp>
#include <sway/gapi/gl/wrap/oglinfohelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLInfoHelper::OGLInfoHelper() {
#ifdef _STUB
  getObjectParameter_ = &OGLInfoHelper::EMU_GetObjectParameter;
  getInfoLog_ = &OGLInfoHelper::EMU_GetInfoLog;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_shader_objects")) {
    getObjectParameter_ = &OGLInfoHelper::ARB_GetObjectParameter;
    getInfoLog_ = &OGLInfoHelper::ARB_GetInfoLog;
  } else {
    getObjectParameter_ = &OGLInfoHelper::STD_GetObjectParameter;
    getInfoLog_ = &OGLInfoHelper::STD_GetInfoLog;
  }

#endif
}

void OGLInfoHelper::EMU_GetObjectParameter(u32_t obj, u32_t pname, i32_t *params) {}

void OGLInfoHelper::STD_GetObjectParameter(u32_t obj, u32_t pname, i32_t *params) {
  // glGetProgramiv(obj, pname, params);
}

void OGLInfoHelper::ARB_GetObjectParameter(u32_t obj, u32_t pname, i32_t *params) {
  OGLInfoExtension::glGetObjectParameterivARB(obj, pname, params);
}

void OGLInfoHelper::EMU_GetInfoLog(u32_t obj, i32_t maxLength, i32_t *length, lpstr_t infoLog) {}

void OGLInfoHelper::STD_GetInfoLog(u32_t obj, i32_t maxLength, i32_t *length, lpstr_t infoLog) {
  // glGetShaderInfoLog(obj, maxLength, length, infoLog);
}

void OGLInfoHelper::ARB_GetInfoLog(u32_t obj, i32_t maxLength, i32_t *length, lpstr_t infoLog) {
  OGLInfoExtension::glGetInfoLogARB(obj, maxLength, length, infoLog);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
