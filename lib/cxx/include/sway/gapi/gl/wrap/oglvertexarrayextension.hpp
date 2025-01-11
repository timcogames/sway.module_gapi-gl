#ifndef SWAY_GAPI_GL_WRAP_OGLVERTEXARRAYEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLVERTEXARRAYEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

class OGLVertexArrayExtension {
public:
  static core::TFunction<void(i32_t, u32_t *)> glGenVertexArraysAPPLE;
  static core::TFunction<void(i32_t, const u32_t *)> glDeleteVertexArraysAPPLE;
  static core::TFunction<void(u32_t)> glBindVertexArrayAPPLE;
  static core::TFunction<bool(u32_t)> glIsVertexArrayAPPLE;

  // Vertex arrays are an extension on OpenGL ES 2.0
  static core::TFunction<void(i32_t, u32_t *)> glGenVertexArraysOES;
  static core::TFunction<void(i32_t, const u32_t *)> glDeleteVertexArraysOES;
  static core::TFunction<void(u32_t)> glBindVertexArrayOES;
  static core::TFunction<bool(u32_t)> glIsVertexArrayOES;

  static void define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &);
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_OGLVERTEXARRAYEXTENSION_HPP
