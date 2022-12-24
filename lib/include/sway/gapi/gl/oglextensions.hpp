#ifndef SWAY_GAPI_GL_EXTENSIONS_HPP
#define SWAY_GAPI_GL_EXTENSIONS_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class Extension {
public:
  static std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> extensions;
  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);

  static core::binding::TFunction<u32_t()> glCreateProgramObject;
  static core::binding::TFunction<void(s32_t num, const u32_t *programs)> glDeletePrograms;
  static core::binding::TFunction<void(u32_t containerObj, u32_t obj)> glAttachObject;
  static core::binding::TFunction<void(u32_t containerObj, u32_t attachedObj)> glDetachObject;
  static core::binding::TFunction<void(u32_t programObj)> glLinkProgram;
  static core::binding::TFunction<void(u32_t programObj)> glValidateProgram;
  static core::binding::TFunction<void(u32_t programObj)> glUseProgramObject;
  static core::binding::TFunction<s32_t(u32_t programObj, lpcstr_t name)> glGetUniformLocation;
  static core::binding::TFunction<void(s32_t location, s32_t val)> glUniform1i;
  static core::binding::TFunction<void(s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3)> glUniform4f;
  static core::binding::TFunction<void(s32_t location, s32_t count, bool transpose, const f32_t *value)>
      glUniformMatrix4fv;
  static core::binding::TFunction<u32_t(u32_t shaderType)> glCreateShaderObject;
  static core::binding::TFunction<void(u32_t obj)> glDeleteShaderObject;
  static core::binding::TFunction<void(u32_t shaderObj, s32_t count, lpcstr_t *string, const s32_t *length)>
      glShaderSource;
  static core::binding::TFunction<void(u32_t shaderObj)> glCompileShader;
  static core::binding::TFunction<void(u32_t obj, u32_t pname, s32_t *params)> glGetObjectParameteriv;
  static core::binding::TFunction<void(u32_t obj, s32_t maxLength, s32_t *length, lpstr_t infoLog)> glGetInfoLog;

  static core::binding::TFunction<void(s32_t num, u32_t *buffers)> glGenBuffers;
  static core::binding::TFunction<void(s32_t num, const u32_t *buffers)> glDeleteBuffers;
  static core::binding::TFunction<void(u32_t target, u32_t buffer)> glBindBuffer;
  static core::binding::TFunction<void(u32_t target, ptrdiff_t size, const void *data, u32_t usage)> glBufferData;
  static core::binding::TFunction<void(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data)>
      glBufferSubData;
  static core::binding::TFunction<void *(u32_t target, u32_t access)> glMapBuffer;
  static core::binding::TFunction<u8_t(u32_t target)> glUnmapBuffer;
  static core::binding::TFunction<u8_t(u32_t buffer)> glIsBuffer;
  static core::binding::TFunction<void(u32_t target, u32_t pname, s32_t *params)> glGetBufferParameteriv;

  static core::binding::TFunction<s32_t(u32_t programObj, lpcstr_t name)> glGetAttribLocation;
  static core::binding::TFunction<void(u32_t index)> glEnableVertexAttribArray;
  static core::binding::TFunction<void(u32_t index)> glDisableVertexAttribArray;
  static core::binding::TFunction<void(
      u32_t index, s32_t size, u32_t type, u8_t normalized, s32_t stride, const void *pointer)>
      glVertexAttribPointer;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_EXTENSIONS_HPP
