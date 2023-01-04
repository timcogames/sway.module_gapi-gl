#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglinfoextension.hpp>
#include <sway/gapi/gl/wrap/oglinfohelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLInfoHelper::OGLInfoHelper() {
#ifdef _STUB
  getObjectParameter_ = &OGLInfoHelper::EMU_getObjectParameter;
  getInfoLog_ = &OGLInfoHelper::EMU_getInfoLog;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_shader_objects")) {
    getObjectParameter_ = &OGLInfoHelper::ARB_getObjectParameter;
    getInfoLog_ = &OGLInfoHelper::ARB_getInfoLog;
  } else {
    getObjectParameter_ = &OGLInfoHelper::STD_getObjectParameter;
    getInfoLog_ = &OGLInfoHelper::STD_getInfoLog;
  }

#endif
}

void OGLInfoHelper::EMU_getObjectParameter(u32_t obj, u32_t pname, s32_t *params) {}

void OGLInfoHelper::STD_getObjectParameter(u32_t obj, u32_t pname, s32_t *params) {
  // glGetProgramiv(obj, pname, params);
}

void OGLInfoHelper::ARB_getObjectParameter(u32_t obj, u32_t pname, s32_t *params) {
  OGLInfoExtension::glGetObjectParameterivARB(obj, pname, params);
}

void OGLInfoHelper::EMU_getInfoLog(u32_t obj, s32_t maxLength, s32_t *length, lpstr_t infoLog) {}

void OGLInfoHelper::STD_getInfoLog(u32_t obj, s32_t maxLength, s32_t *length, lpstr_t infoLog) {
  // glGetShaderInfoLog(obj, maxLength, length, infoLog);
}

void OGLInfoHelper::ARB_getInfoLog(u32_t obj, s32_t maxLength, s32_t *length, lpstr_t infoLog) {
  OGLInfoExtension::glGetInfoLogARB(obj, maxLength, length, infoLog);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
