#ifndef SWAY_GAPI_GL_WRAP_OGLINFOEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLINFOEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLInfoExtension {
public:
  static core::binding::TFunction<void(u32_t, u32_t, i32_t *)> glGetObjectParameterivARB;
  static core::binding::TFunction<void(u32_t, i32_t, i32_t *, lpstr_t)> glGetInfoLogARB;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLINFOEXTENSION_HPP
