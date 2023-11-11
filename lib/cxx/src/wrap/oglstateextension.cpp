#include <sway/gapi/gl/wrap/oglstateextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(u32_t, u32_t, u32_t, u32_t)> OGLStateExtension::glBlendFuncSeparateEXT = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OGLStateExtension::glBlendEquationSeparateEXT = nullptr;

void OGLStateExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glBlendFuncSeparateEXT = extensions({{"GL_EXT_blend_func_separate", "glBlendFuncSeparateEXT"}});
  glBlendEquationSeparateEXT = extensions({{"GL_EXT_blend_equation_separate", "glBlendEquationSeparateEXT"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
