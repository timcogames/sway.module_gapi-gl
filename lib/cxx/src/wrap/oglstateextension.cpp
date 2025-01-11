#include <sway/gapi/gl/wrap/oglstateextension.hpp>

namespace sway::gapi {

core::TFunction<void(u32_t, u32_t, u32_t, u32_t)> OGLStateExtension::glBlendFuncSeparateEXT = nullptr;
core::TFunction<void(u32_t, u32_t)> OGLStateExtension::glBlendEquationSeparateEXT = nullptr;

void OGLStateExtension::define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &exts) {
  glBlendFuncSeparateEXT = exts({{"GL_EXT_blend_func_separate", "glBlendFuncSeparateEXT"}});
  glBlendEquationSeparateEXT = exts({{"GL_EXT_blend_equation_separate", "glBlendEquationSeparateEXT"}});
}

}  // namespace sway::gapi
