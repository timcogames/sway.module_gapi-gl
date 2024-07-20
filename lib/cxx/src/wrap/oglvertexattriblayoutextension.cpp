#include <sway/gapi/gl/wrap/oglvertexattriblayoutextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(u32_t)> OGLVertexAttribLayoutExtension::glEnableVertexAttribArrayARB = nullptr;
core::binding::TFunction<void(u32_t)> OGLVertexAttribLayoutExtension::glDisableVertexAttribArrayARB = nullptr;
core::binding::TFunction<void(u32_t, i32_t, u32_t, u8_t, i32_t, const void *)>
    OGLVertexAttribLayoutExtension::glVertexAttribPointerARB = nullptr;

void OGLVertexAttribLayoutExtension::define(
    const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glEnableVertexAttribArrayARB = extensions({{"GL_ARB_vertex_program", "glEnableVertexAttribArrayARB"}});
  glDisableVertexAttribArrayARB = extensions({{"GL_ARB_vertex_program", "glDisableVertexAttribArrayARB"}});
  glVertexAttribPointerARB = extensions({{"GL_ARB_vertex_program", "glVertexAttribPointerARB"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
