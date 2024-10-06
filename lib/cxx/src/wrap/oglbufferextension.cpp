#include <sway/gapi/gl/wrap/oglbufferextension.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

core::binding::TFunction<void(i32_t, u32_t *)> OGLBufferExtension::glGenBuffersARB = nullptr;
core::binding::TFunction<void(i32_t, const u32_t *)> OGLBufferExtension::glDeleteBuffersARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OGLBufferExtension::glBindBufferARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t, u32_t, ptrdiff_t, ptrdiff_t)> OGLBufferExtension::glBindBufferRangeEXT =
    nullptr;
core::binding::TFunction<void(u32_t, ptrdiff_t, const void *, u32_t)> OGLBufferExtension::glBufferDataARB = nullptr;
core::binding::TFunction<void(u32_t, ptrdiff_t, ptrdiff_t, const void *)> OGLBufferExtension::glBufferSubDataARB =
    nullptr;
core::binding::TFunction<void *(u32_t, i32_t, i32_t, u32_t)> OGLBufferExtension::glMapBufferRangeEXT = nullptr;
core::binding::TFunction<void *(u32_t, u32_t)> OGLBufferExtension::glMapBufferARB = nullptr;
core::binding::TFunction<void *(u32_t, u32_t)> OGLBufferExtension::glMapBufferOES = nullptr;
core::binding::TFunction<u8_t(u32_t)> OGLBufferExtension::glUnmapBufferARB = nullptr;
core::binding::TFunction<u8_t(u32_t)> OGLBufferExtension::glUnmapBufferOES = nullptr;
core::binding::TFunction<u8_t(u32_t)> OGLBufferExtension::glIsBufferARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t, i32_t *)> OGLBufferExtension::glGetBufferParameterivARB = nullptr;

void OGLBufferExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glGenBuffersARB = exts({{"GL_ARB_vertex_buffer_object", "glGenBuffersARB"}});
  glDeleteBuffersARB = exts({{"GL_ARB_vertex_buffer_object", "glDeleteBuffersARB"}});
  glBindBufferARB = exts({{"GL_ARB_vertex_buffer_object", "glBindBufferARB"}});
  glBindBufferRangeEXT = exts({{"GL_EXT_transform_feedback", "glBindBufferRangeEXT"}});
  glBufferDataARB = exts({{"GL_ARB_vertex_buffer_object", "glBufferDataARB"}});
  glBufferSubDataARB = exts({{"GL_ARB_vertex_buffer_object", "glBufferSubDataARB"}});
  glMapBufferRangeEXT = exts({{"GL_EXT_map_buffer_range", "glMapBufferRangeEXT"}});
  glMapBufferARB = exts({{"GL_ARB_vertex_buffer_object", "glMapBufferARB"}});
  glMapBufferOES = exts({{"GL_OES_mapbuffer", "glMapBufferOES"}});
  glUnmapBufferARB = exts({{"GL_ARB_vertex_buffer_object", "glUnmapBufferARB"}});
  glUnmapBufferOES = exts({{"GL_OES_mapbuffer", "glUnmapBufferOES"}});
  glIsBufferARB = exts({{"GL_ARB_vertex_buffer_object", "glIsBufferARB"}});
  glGetBufferParameterivARB = exts({{"GL_ARB_vertex_buffer_object", "glGetBufferParameterivARB"}});
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
