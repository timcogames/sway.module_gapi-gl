#include <sway/gapi/gl/wrap/oglvertexarrayextension.hpp>

namespace sway::gapi {

core::TFunctionPointer<void(i32_t, u32_t *)> OGLVertexArrayExtension::glGenVertexArraysAPPLE = nullptr;
core::TFunctionPointer<void(i32_t, const u32_t *)> OGLVertexArrayExtension::glDeleteVertexArraysAPPLE = nullptr;
core::TFunctionPointer<void(u32_t)> OGLVertexArrayExtension::glBindVertexArrayAPPLE = nullptr;
core::TFunctionPointer<bool(u32_t)> OGLVertexArrayExtension::glIsVertexArrayAPPLE = nullptr;

void OGLVertexArrayExtension::define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glGenVertexArraysAPPLE = exts({{"GL_APPLE_vertex_array_object", "glGenVertexArraysAPPLE"}});
  glDeleteVertexArraysAPPLE = exts({{"GL_APPLE_vertex_array_object", "glDeleteVertexArraysAPPLE"}});
  glBindVertexArrayAPPLE = exts({{"GL_APPLE_vertex_array_object", "glBindVertexArrayAPPLE"}});
  glIsVertexArrayAPPLE = exts({{"GL_APPLE_vertex_array_object", "glIsVertexArrayAPPLE"}});
}

}  // namespace sway::gapi
