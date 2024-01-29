#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

EXTERN_C_BEGIN

D_MODULE_GAPI_GL_INTERFACE_EXPORT_API core::PluginInfo pluginGetInfo() {
  core::PluginInfo info = {};
  return info;
}

D_MODULE_GAPI_GL_INTERFACE_EXPORT_API void pluginInitialize(core::PluginFunctionSet *functions) {
  static_cast<ConcreatePluginFunctionSet *>(functions)->createCapability =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLCapability::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createShader =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLGenericShader::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createShaderProgram =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLShaderProgram::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createIdGenerator =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLBufferIdGenerator::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createBuffer =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLGenericBuffer::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createVertexArray =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLVertexArray::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createVertexAttribLayout =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLVertexAttribLayout::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createTexture =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLTexture::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createTextureSampler =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLTextureSampler::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createDrawCall =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLDrawCall::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createViewport =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLViewport::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createStateContext =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLStateContext::createInstance);
}

EXTERN_C_END

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
