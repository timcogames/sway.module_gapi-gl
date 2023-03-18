#include <sway/gapi/gl/wrap/oglstateextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<void(u32_t, u32_t, u32_t, u32_t)> OGLStateExtension::glBlendFuncSeparateEXT = nullptr;
core::binding::TFunction<void(u32_t, u32_t, u32_t, u32_t, u32_t)> OGLStateExtension::glBlendFuncSeparateiARB = nullptr;
core::binding::TFunction<void(u32_t, u32_t)> OGLStateExtension::glBlendEquationSeparateEXT = nullptr;
core::binding::TFunction<void(u32_t, u32_t, u32_t)> OGLStateExtension::glBlendEquationSeparateiARB = nullptr;

void OGLStateExtension::define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &extensions) {
  glBlendFuncSeparateEXT = extensions({{"GL_EXT_blend_func_separate", "glBlendFuncSeparateEXT"}});
  glBlendFuncSeparateiARB = extensions({{"GL_ARB_draw_buffers_blend", "glBlendFuncSeparateiARB"}});
  glBlendEquationSeparateEXT = extensions({{"GL_EXT_blend_equation_separate", "glBlendEquationSeparateEXT"}});
  glBlendEquationSeparateiARB = extensions({{"GL_ARB_draw_buffers_blend", "glBlendEquationSeparateiARB"}});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
