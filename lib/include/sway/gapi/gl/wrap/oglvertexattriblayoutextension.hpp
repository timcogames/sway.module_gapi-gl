#ifndef SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLVertexAttribLayoutExtension {
public:
  static core::binding::TFunction<void(u32_t)> glEnableVertexAttribArrayARB;
  static core::binding::TFunction<void(u32_t)> glDisableVertexAttribArrayARB;
  static core::binding::TFunction<void(u32_t, s32_t, u32_t, u8_t, s32_t, const void *)> glVertexAttribPointerARB;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTEXTENSION_HPP
