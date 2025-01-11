#ifndef SWAY_GAPI_GL_WRAP_OGLINFOEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLINFOEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

class OGLInfoExtension {
public:
  static core::TFunction<void(u32_t, u32_t, i32_t *)> glGetObjectParameterivARB;
  static core::TFunction<void(u32_t, i32_t, i32_t *, lpstr_t)> glGetInfoLogARB;

  static void define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &);
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_OGLINFOEXTENSION_HPP
