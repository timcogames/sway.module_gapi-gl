#ifndef SWAY_GAPI_GL_WRAP_OGLSTATEEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLSTATEEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

class OGLStateExtension {
public:
  static core::TFunction<void(u32_t, u32_t, u32_t, u32_t)> glBlendFuncSeparateEXT;
  static core::TFunction<void(u32_t, u32_t)> glBlendEquationSeparateEXT;

  static void define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &);
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_OGLSTATEEXTENSION_HPP
