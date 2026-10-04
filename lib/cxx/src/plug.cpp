#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/gapiplugin.hpp>

namespace sway::gapi {

EXTERN_C_BEGIN

D_MODULE_GAPI_GL_INTERFACE_EXPORT_API core::PluginInfo pluginGetInfo() {
  core::PluginInfo info = {};
  return info;
}

D_MODULE_GAPI_GL_INTERFACE_EXPORT_API void pluginInitialize(core::PluginFunctionSetBase *functions) {
  auto *funcs = static_cast<ConcretePluginFunctionSet *>(functions);

  funcs->createCapability_ =
      CreateCapabilityFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLCapability::createInstance));
  funcs->createShader_ = CreateShaderFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLGenericShader::createInstance));
  funcs->createShaderProgram_ =
      CreateShaderProgramFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLShaderProgram::createInstance));
  funcs->createShaderPreprocessor_ =
      CreateShaderPreprocessorFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLShaderPreprocessor::createInstance));
  funcs->createBufferIdGenerator_ =
      CreateBufferIdGeneratorFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLGenericBufferIdGenerator::createInstance));
  funcs->createBuffer_ = CreateBufferFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLGenericBuffer::createInstance));
  funcs->createFrameBufferIdGenerator_ = CreateFrameBufferIdGeneratorFunc_t(
      reinterpret_cast<core::ProcAddress_t>(OGLIdGenerator<IdGeneratorType::Enum::FRAME_BUFFER>::createInstance));
  funcs->createFrameBuffer_ =
      CreateFrameBufferFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLFrameBuffer::createInstance));
  funcs->createRenderBuffer_ =
      CreateRenderBufferFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLRenderBuffer::createInstance));
  funcs->createVertexArray_ =
      CreateVertexArrayFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLVertexArray::createInstance));
  funcs->createVertexAttribLayout_ =
      CreateVertexAttribLayoutFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLVertexAttribLayout::createInstance));
  funcs->createTextureIdGenerator_ =
      CreateTextureIdGeneratorFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLTextureIdGenerator::createInstance));
  funcs->createTexture_ = CreateTextureFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLTexture::createInstance));
  funcs->createTextureSampler_ =
      CreateTextureSamplerFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLTextureSampler::createInstance));
  funcs->createDrawCall_ = CreateDrawCallFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLDrawCall::createInstance));
  funcs->createViewport_ = CreateViewportFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLViewport::createInstance));
  funcs->createStateContext_ =
      CreateStateContextFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLStateContext::createInstance));
  funcs->createRasterizerState_ =
      CreateRasterizerStateFunc_t(reinterpret_cast<core::ProcAddress_t>(OGLRasterizerState::createInstance));
}

EXTERN_C_END

}  // namespace sway::gapi
