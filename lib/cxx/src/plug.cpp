#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

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
  static_cast<ConcreatePluginFunctionSet *>(functions)->createShaderPreprocessor =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLShaderPreprocessor::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createBufferIdGenerator =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLGenericBufferIdGenerator::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createBuffer =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLGenericBuffer::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createFrameBufferIdGenerator =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLFrameBufferIdGenerator::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createFrameBuffer =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLFrameBuffer::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createRenderBuffer =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLRenderBuffer::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createVertexArray =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLVertexArray::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createVertexAttribLayout =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLVertexAttribLayout::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createTextureIdGenerator =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLTextureIdGenerator::createInstance);
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
  static_cast<ConcreatePluginFunctionSet *>(functions)->createRasterizerState =
      reinterpret_cast<core::binding::ProcAddress_t>(OGLRasterizerState::createInstance);
}

EXTERN_C_END

NS_END()  // namespace gapi
NS_END()  // namespace sway
