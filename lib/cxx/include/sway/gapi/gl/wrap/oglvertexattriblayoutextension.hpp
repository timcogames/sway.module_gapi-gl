#ifndef SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

class OGLVertexAttribLayoutExtension {
public:
  static core::TFunction<void(u32_t)> glEnableVertexAttribArrayARB;
  static core::TFunction<void(u32_t)> glDisableVertexAttribArrayARB;
  static core::TFunction<void(u32_t, i32_t, u32_t, u8_t, i32_t, const void *)> glVertexAttribPointerARB;

  static void define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &);
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTEXTENSION_HPP
