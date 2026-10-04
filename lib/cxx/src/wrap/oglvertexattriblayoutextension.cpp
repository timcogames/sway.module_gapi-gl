#include <sway/gapi/gl/wrap/oglvertexattriblayoutextension.hpp>

namespace sway::gapi {

core::TFunctionPointer<void(u32_t)> OGLVertexAttribLayoutExtension::glEnableVertexAttribArrayARB = nullptr;
core::TFunctionPointer<void(u32_t)> OGLVertexAttribLayoutExtension::glDisableVertexAttribArrayARB = nullptr;
core::TFunctionPointer<void(u32_t, i32_t, u32_t, u8_t, i32_t, const void *)>
    OGLVertexAttribLayoutExtension::glVertexAttribPointerARB = nullptr;

void OGLVertexAttribLayoutExtension::define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glEnableVertexAttribArrayARB = exts({{"GL_ARB_vertex_program", "glEnableVertexAttribArrayARB"}});
  glDisableVertexAttribArrayARB = exts({{"GL_ARB_vertex_program", "glDisableVertexAttribArrayARB"}});
  glVertexAttribPointerARB = exts({{"GL_ARB_vertex_program", "glVertexAttribPointerARB"}});
}

}  // namespace sway::gapi
