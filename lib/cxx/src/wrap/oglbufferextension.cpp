#include <sway/gapi/gl/wrap/oglbufferextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(s32_t, u32_t *)> OGLBufferExtension::glGenBuffersARB = nullptr;
core::binding::TFunction<void(s32_t, const u32_t *)> OGLBufferExtension::glDeleteBuffersARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OGLBufferExtension::glBindBufferARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t, u32_t, ptrdiff_t, ptrdiff_t)> OGLBufferExtension::glBindBufferRangeEXT =
    nullptr;
core::binding::TFunction<void(u32_t, ptrdiff_t, const void *, u32_t)> OGLBufferExtension::glBufferDataARB = nullptr;
core::binding::TFunction<void(u32_t, ptrdiff_t, ptrdiff_t, const void *)> OGLBufferExtension::glBufferSubDataARB =
    nullptr;
core::binding::TFunction<void *(u32_t, s32_t, s32_t, u32_t)> OGLBufferExtension::glMapBufferRangeEXT = nullptr;
core::binding::TFunction<void *(u32_t, u32_t)> OGLBufferExtension::glMapBufferARB = nullptr;
core::binding::TFunction<void *(u32_t, u32_t)> OGLBufferExtension::glMapBufferOES = nullptr;
core::binding::TFunction<u8_t(u32_t)> OGLBufferExtension::glUnmapBufferARB = nullptr;
core::binding::TFunction<u8_t(u32_t)> OGLBufferExtension::glUnmapBufferOES = nullptr;
core::binding::TFunction<u8_t(u32_t)> OGLBufferExtension::glIsBufferARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t, s32_t *)> OGLBufferExtension::glGetBufferParameterivARB = nullptr;

void OGLBufferExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glGenBuffersARB = extensions({{"GL_ARB_vertex_buffer_object", "glGenBuffersARB"}});
  glDeleteBuffersARB = extensions({{"GL_ARB_vertex_buffer_object", "glDeleteBuffersARB"}});
  glBindBufferARB = extensions({{"GL_ARB_vertex_buffer_object", "glBindBufferARB"}});
  glBindBufferRangeEXT = extensions({{"GL_EXT_transform_feedback", "glBindBufferRangeEXT"}});
  glBufferDataARB = extensions({{"GL_ARB_vertex_buffer_object", "glBufferDataARB"}});
  glBufferSubDataARB = extensions({{"GL_ARB_vertex_buffer_object", "glBufferSubDataARB"}});
  glMapBufferRangeEXT = extensions({{"GL_EXT_map_buffer_range", "glMapBufferRangeEXT"}});
  glMapBufferARB = extensions({{"GL_ARB_vertex_buffer_object", "glMapBufferARB"}});
  glMapBufferOES = extensions({{"GL_OES_mapbuffer", "glMapBufferOES"}});
  glUnmapBufferARB = extensions({{"GL_ARB_vertex_buffer_object", "glUnmapBufferARB"}});
  glUnmapBufferOES = extensions({{"GL_OES_mapbuffer", "glUnmapBufferOES"}});
  glIsBufferARB = extensions({{"GL_ARB_vertex_buffer_object", "glIsBufferARB"}});
  glGetBufferParameterivARB = extensions({{"GL_ARB_vertex_buffer_object", "glGetBufferParameterivARB"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
