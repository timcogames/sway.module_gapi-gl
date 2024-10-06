#ifndef SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLVertexAttribLayoutExtension {
public:
  static core::binding::TFunction<void(u32_t)> glEnableVertexAttribArrayARB;
  static core::binding::TFunction<void(u32_t)> glDisableVertexAttribArrayARB;
  static core::binding::TFunction<void(u32_t, i32_t, u32_t, u8_t, i32_t, const void *)> glVertexAttribPointerARB;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTEXTENSION_HPP
