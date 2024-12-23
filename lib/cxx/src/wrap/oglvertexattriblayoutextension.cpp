#include <sway/gapi/gl/wrap/oglvertexattriblayoutextension.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

core::binding::TFunction<void(u32_t)> OGLVertexAttribLayoutExtension::glEnableVertexAttribArrayARB = nullptr;
core::binding::TFunction<void(u32_t)> OGLVertexAttribLayoutExtension::glDisableVertexAttribArrayARB = nullptr;
core::binding::TFunction<void(u32_t, i32_t, u32_t, u8_t, i32_t, const void *)>
    OGLVertexAttribLayoutExtension::glVertexAttribPointerARB = nullptr;

void OGLVertexAttribLayoutExtension::define(
    const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glEnableVertexAttribArrayARB = exts({{"GL_ARB_vertex_program", "glEnableVertexAttribArrayARB"}});
  glDisableVertexAttribArrayARB = exts({{"GL_ARB_vertex_program", "glDisableVertexAttribArrayARB"}});
  glVertexAttribPointerARB = exts({{"GL_ARB_vertex_program", "glVertexAttribPointerARB"}});
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
