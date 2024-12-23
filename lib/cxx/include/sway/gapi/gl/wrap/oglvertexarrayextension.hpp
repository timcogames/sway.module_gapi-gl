#ifndef SWAY_GAPI_GL_WRAP_OGLVERTEXARRAYEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLVERTEXARRAYEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLVertexArrayExtension {
public:
  static core::binding::TFunction<void(i32_t, u32_t *)> glGenVertexArraysAPPLE;
  static core::binding::TFunction<void(i32_t, const u32_t *)> glDeleteVertexArraysAPPLE;
  static core::binding::TFunction<void(u32_t)> glBindVertexArrayAPPLE;
  static core::binding::TFunction<bool(u32_t)> glIsVertexArrayAPPLE;

  // Vertex arrays are an extension on OpenGL ES 2.0
  static core::binding::TFunction<void(i32_t, u32_t *)> glGenVertexArraysOES;
  static core::binding::TFunction<void(i32_t, const u32_t *)> glDeleteVertexArraysOES;
  static core::binding::TFunction<void(u32_t)> glBindVertexArrayOES;
  static core::binding::TFunction<bool(u32_t)> glIsVertexArrayOES;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_WRAP_OGLVERTEXARRAYEXTENSION_HPP
