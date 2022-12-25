#include <sway/gapi/gl/wrap/openglbufferextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(s32_t, u32_t *)> OpenGLBufferExtension::glGenBuffersARB = nullptr;
core::binding::TFunction<void(s32_t, const u32_t *)> OpenGLBufferExtension::glDeleteBuffersARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OpenGLBufferExtension::glBindBufferARB = nullptr;
core::binding::TFunction<void(u32_t, ptrdiff_t, const void *, u32_t)> OpenGLBufferExtension::glBufferDataARB = nullptr;
core::binding::TFunction<void(u32_t, ptrdiff_t, ptrdiff_t, const void *)> OpenGLBufferExtension::glBufferSubDataARB =
    nullptr;
// core::binding::TFunction<void *(u32_t, u32_t)> OpenGLBufferExtension::glMapBufferARB = nullptr;
// core::binding::TFunction<u8_t(u32_t)> OpenGLBufferExtension::glUnmapBufferARB = nullptr;
core::binding::TFunction<u8_t(u32_t)> OpenGLBufferExtension::glIsBufferARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t, s32_t *)> OpenGLBufferExtension::glGetBufferParameterivARB = nullptr;

void OpenGLBufferExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glGenBuffersARB = extensions({{"GL_ARB_vertex_buffer_object", "glGenBuffersARB"}});
  glDeleteBuffersARB = extensions({{"GL_ARB_vertex_buffer_object", "glDeleteBuffersARB"}});
  glBindBufferARB = extensions({{"GL_ARB_vertex_buffer_object", "glBindBufferARB"}});
  glBufferDataARB = extensions({{"GL_ARB_vertex_buffer_object", "glBufferDataARB"}});
  glBufferSubDataARB = extensions({{"GL_ARB_vertex_buffer_object", "glBufferSubDataARB"}});
  // glMapBufferARB = extensions({{"GL_ARB_vertex_buffer_object", "glMapBufferARB"}});
  // glUnmapBufferARB = extensions({{"GL_ARB_vertex_buffer_object", "glUnmapBufferARB"}});
  glIsBufferARB = extensions({{"GL_ARB_vertex_buffer_object", "glIsBufferARB"}});
  glGetBufferParameterivARB = extensions({{"GL_ARB_vertex_buffer_object", "glGetBufferParameterivARB"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
