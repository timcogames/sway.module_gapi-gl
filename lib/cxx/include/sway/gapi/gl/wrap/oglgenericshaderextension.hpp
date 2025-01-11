#ifndef SWAY_GAPI_GL_WRAP_OGLGENERICSHADEREXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLGENERICSHADEREXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

class OGLGenericShaderExtension {
public:
  static core::TFunction<u32_t(u32_t)> glCreateShaderObjectARB;
  static core::TFunction<void(u32_t)> glDeleteObjectARB;
  static core::TFunction<void(u32_t, i32_t, lpcstr_t *, const i32_t *)> glShaderSourceARB;
  static core::TFunction<void(u32_t)> glCompileShaderARB;
  static core::TFunction<i32_t(u32_t, lpcstr_t)> glGetAttribLocationARB;

  static void define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &);
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_OGLGENERICSHADEREXTENSION_HPP
