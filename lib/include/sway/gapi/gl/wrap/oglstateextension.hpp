#ifndef SWAY_GAPI_GL_WRAP_OGLSTATEEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLSTATEEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLStateExtension {
public:
  static core::binding::TFunction<void(u32_t, u32_t, u32_t, u32_t)> glBlendFuncSeparateEXT;
  static core::binding::TFunction<void(u32_t, u32_t)> glBlendEquationSeparateEXT;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLSTATEEXTENSION_HPP
