#ifndef SWAY_GAPI_GL_WRAP_OGLSHADERPROGRAMEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLSHADERPROGRAMEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLShaderProgramExtension {
public:
  static core::binding::TFunction<u32_t()> glCreateProgramObjectARB;
  static core::binding::TFunction<void(i32_t, const u32_t *)> glDeleteProgramsARB;
  static core::binding::TFunction<void(u32_t, u32_t)> glAttachObjectARB;
  static core::binding::TFunction<void(u32_t, u32_t)> glDetachObjectARB;
  static core::binding::TFunction<void(u32_t)> glLinkProgramARB;
  static core::binding::TFunction<void(u32_t)> glValidateProgramARB;
  static core::binding::TFunction<void(u32_t)> glUseProgramObjectARB;
  static core::binding::TFunction<i32_t(u32_t, lpcstr_t)> glGetUniformLocationARB;
  static core::binding::TFunction<void(i32_t, i32_t)> glUniform1iARB;
  static core::binding::TFunction<void(i32_t, f32_t)> glUniform1fARB;
  static core::binding::TFunction<void(i32_t, f32_t, f32_t, f32_t, f32_t)> glUniform4fARB;
  static core::binding::TFunction<void(i32_t, i32_t, f32_t *)> glUniform4fvARB;
  static core::binding::TFunction<void(i32_t, i32_t, bool, const f32_t *)> glUniformMatrix4fvARB;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLSHADERPROGRAMEXTENSION_HPP
