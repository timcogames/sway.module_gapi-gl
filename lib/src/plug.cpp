#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

DLLAPI_EXPORT core::PluginInfo pluginGetInfo() {
  core::PluginInfo info = {};
  return info;
}

DLLAPI_EXPORT void pluginInitialize(core::PluginFunctionSet *functions) {
  static_cast<ConcreatePluginFunctionSet *>(functions)->createCapability =
      reinterpret_cast<core::binding::ProcAddress_t>(Capability::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createShader =
      reinterpret_cast<core::binding::ProcAddress_t>(GenericShader::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createShaderProgram =
      reinterpret_cast<core::binding::ProcAddress_t>(ShaderProgram::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createIdGenerator =
      reinterpret_cast<core::binding::ProcAddress_t>(BufferIdGenerator<u32_t>::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createBuffer =
      reinterpret_cast<core::binding::ProcAddress_t>(GenericBuffer::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createVertexAttribLayout =
      reinterpret_cast<core::binding::ProcAddress_t>(GenericVertexAttribLayout::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createDrawCall =
      reinterpret_cast<core::binding::ProcAddress_t>(DrawCall::createInstance);
  static_cast<ConcreatePluginFunctionSet *>(functions)->createViewport =
      reinterpret_cast<core::binding::ProcAddress_t>(Viewport::createInstance);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
