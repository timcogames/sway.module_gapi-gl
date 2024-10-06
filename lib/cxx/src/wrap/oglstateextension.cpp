#include <sway/gapi/gl/wrap/oglstateextension.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

core::binding::TFunction<void(u32_t, u32_t, u32_t, u32_t)> OGLStateExtension::glBlendFuncSeparateEXT = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OGLStateExtension::glBlendEquationSeparateEXT = nullptr;

void OGLStateExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glBlendFuncSeparateEXT = exts({{"GL_EXT_blend_func_separate", "glBlendFuncSeparateEXT"}});
  glBlendEquationSeparateEXT = exts({{"GL_EXT_blend_equation_separate", "glBlendEquationSeparateEXT"}});
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
