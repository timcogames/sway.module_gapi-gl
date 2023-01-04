#include <sway/gapi/gl/wrap/oglbufferextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(s32_t, u32_t *)> OGLBufferExtension::glGenBuffersARB = nullptr;
core::binding::TFunction<void(s32_t, const u32_t *)> OGLBufferExtension::glDeleteBuffersARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OGLBufferExtension::glBindBufferARB = nullptr;
core::binding::TFunction<void(u32_t, ptrdiff_t, const void *, u32_t)> OGLBufferExtension::glBufferDataARB = nullptr;
core::binding::TFunction<void(u32_t, ptrdiff_t, ptrdiff_t, const void *)> OGLBufferExtension::glBufferSubDataARB =
    nullptr;
core::binding::TFunction<u8_t(u32_t)> OGLBufferExtension::glIsBufferARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t, s32_t *)> OGLBufferExtension::glGetBufferParameterivARB = nullptr;

void OGLBufferExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glGenBuffersARB = extensions({{"GL_ARB_vertex_buffer_object", "glGenBuffersARB"}});
  glDeleteBuffersARB = extensions({{"GL_ARB_vertex_buffer_object", "glDeleteBuffersARB"}});
  glBindBufferARB = extensions({{"GL_ARB_vertex_buffer_object", "glBindBufferARB"}});
  glBufferDataARB = extensions({{"GL_ARB_vertex_buffer_object", "glBufferDataARB"}});
  glBufferSubDataARB = extensions({{"GL_ARB_vertex_buffer_object", "glBufferSubDataARB"}});
  glIsBufferARB = extensions({{"GL_ARB_vertex_buffer_object", "glIsBufferARB"}});
  glGetBufferParameterivARB = extensions({{"GL_ARB_vertex_buffer_object", "glGetBufferParameterivARB"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
