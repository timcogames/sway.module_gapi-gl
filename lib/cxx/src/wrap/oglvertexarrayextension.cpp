#include <sway/gapi/gl/wrap/oglvertexarrayextension.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

core::binding::TFunction<void(i32_t, u32_t *)> OGLVertexArrayExtension::glGenVertexArraysAPPLE = nullptr;
core::binding::TFunction<void(i32_t, const u32_t *)> OGLVertexArrayExtension::glDeleteVertexArraysAPPLE = nullptr;
core::binding::TFunction<void(u32_t)> OGLVertexArrayExtension::glBindVertexArrayAPPLE = nullptr;
core::binding::TFunction<bool(u32_t)> OGLVertexArrayExtension::glIsVertexArrayAPPLE = nullptr;

void OGLVertexArrayExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glGenVertexArraysAPPLE = exts({{"GL_APPLE_vertex_array_object", "glGenVertexArraysAPPLE"}});
  glDeleteVertexArraysAPPLE = exts({{"GL_APPLE_vertex_array_object", "glDeleteVertexArraysAPPLE"}});
  glBindVertexArrayAPPLE = exts({{"GL_APPLE_vertex_array_object", "glBindVertexArrayAPPLE"}});
  glIsVertexArrayAPPLE = exts({{"GL_APPLE_vertex_array_object", "glIsVertexArrayAPPLE"}});
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
