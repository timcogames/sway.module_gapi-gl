#ifndef SWAY_GAPI_GL_WRAP_OGLGENERICSHADEREXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLGENERICSHADEREXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLGenericShaderExtension {
public:
  static core::binding::TFunction<u32_t(u32_t)> glCreateShaderObjectARB;
  static core::binding::TFunction<void(u32_t)> glDeleteObjectARB;
  static core::binding::TFunction<void(u32_t, i32_t, lpcstr_t *, const i32_t *)> glShaderSourceARB;
  static core::binding::TFunction<void(u32_t)> glCompileShaderARB;
  static core::binding::TFunction<i32_t(u32_t, lpcstr_t)> glGetAttribLocationARB;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLGENERICSHADEREXTENSION_HPP
