#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglgenericbufferhelper.hpp>
#include <sway/gapi/gl/wrap/openglbufferextension.hpp>

#define GL_GLEXT_PROTOTYPES 1
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLGenericBufferHelper::OGLGenericBufferHelper() {
#ifdef _STUB
  GenerateBuffers_ = &OGLGenericBufferHelper::EMU_GenerateBuffers;
  DeleteBuffers_ = &OGLGenericBufferHelper::EMU_DeleteBuffers;
  BindBuffer_ = &OGLGenericBufferHelper::EMU_BindBuffer;
  BufferData_ = &OGLGenericBufferHelper::EMU_BufferData;
  BufferSubData_ = &OGLGenericBufferHelper::EMU_BufferSubData;
  isBuffer_ = &OGLGenericBufferHelper::EMU_isBuffer;
  GetBufferParam_ = &OGLGenericBufferHelper::EMU_GetBufferParam;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_vertex_buffer_object")) {
    GenerateBuffers_ = &OGLGenericBufferHelper::ARB_GenerateBuffers;
    DeleteBuffers_ = &OGLGenericBufferHelper::ARB_DeleteBuffers;
    BindBuffer_ = &OGLGenericBufferHelper::ARB_BindBuffer;
    BufferData_ = &OGLGenericBufferHelper::ARB_BufferData;
    BufferSubData_ = &OGLGenericBufferHelper::ARB_BufferSubData;
    isBuffer_ = &OGLGenericBufferHelper::ARB_isBuffer;
    GetBufferParam_ = &OGLGenericBufferHelper::ARB_GetBufferParam;
  } else {
    GenerateBuffers_ = &OGLGenericBufferHelper::STD_GenerateBuffers;
    DeleteBuffers_ = &OGLGenericBufferHelper::STD_DeleteBuffers;
    BindBuffer_ = &OGLGenericBufferHelper::STD_BindBuffer;
    BufferData_ = &OGLGenericBufferHelper::STD_BufferData;
    BufferSubData_ = &OGLGenericBufferHelper::STD_BufferSubData;
    isBuffer_ = &OGLGenericBufferHelper::STD_isBuffer;
    GetBufferParam_ = &OGLGenericBufferHelper::STD_GetBufferParam;
  }

#endif
}

void OGLGenericBufferHelper::EMU_GenerateBuffers(u32_t latest, u32_t num, u32_t *ids) {
  for (auto i = 0; i < (s32_t)num; ++i) {
    ids[i] = i + latest + 1;
  }
}

void OGLGenericBufferHelper::STD_GenerateBuffers([[maybe_unused]] u32_t latest, u32_t num, u32_t *ids) {
  glGenBuffers(num, ids);
}

void OGLGenericBufferHelper::ARB_GenerateBuffers([[maybe_unused]] u32_t latest, u32_t num, u32_t *ids) {
  OpenGLBufferExtension::glGenBuffersARB(num, ids);
}

void OGLGenericBufferHelper::EMU_DeleteBuffers([[maybe_unused]] u32_t num, [[maybe_unused]] u32_t *ids) {}

void OGLGenericBufferHelper::STD_DeleteBuffers(u32_t num, u32_t *ids) { glDeleteBuffers(num, ids); }

void OGLGenericBufferHelper::ARB_DeleteBuffers(u32_t num, u32_t *ids) {
  OpenGLBufferExtension::glDeleteBuffersARB(num, ids);
}

void OGLGenericBufferHelper::EMU_BindBuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t buffer) {}

void OGLGenericBufferHelper::STD_BindBuffer(u32_t target, u32_t buffer) { glBindBuffer(target, buffer); }

void OGLGenericBufferHelper::ARB_BindBuffer(u32_t target, u32_t buffer) {
  OpenGLBufferExtension::glBindBufferARB(target, buffer);
}

void OGLGenericBufferHelper::EMU_BufferData([[maybe_unused]] u32_t target, [[maybe_unused]] ptrdiff_t size,
    [[maybe_unused]] const void *data, [[maybe_unused]] u32_t usage) {}

void OGLGenericBufferHelper::STD_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage) {
  glBufferData(target, size, data, usage);
}

void OGLGenericBufferHelper::ARB_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage) {
  OpenGLBufferExtension::glBufferDataARB(target, size, data, usage);
}

void OGLGenericBufferHelper::EMU_BufferSubData([[maybe_unused]] u32_t target, [[maybe_unused]] ptrdiff_t offset,
    [[maybe_unused]] ptrdiff_t size, [[maybe_unused]] const void *data) {}

void OGLGenericBufferHelper::STD_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  glBufferSubData(target, offset, size, data);
}

void OGLGenericBufferHelper::ARB_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  OpenGLBufferExtension::glBufferSubDataARB(target, offset, size, data);
}

auto OGLGenericBufferHelper::EMU_isBuffer([[maybe_unused]] u32_t target) -> u8_t { return true; }

auto OGLGenericBufferHelper::STD_isBuffer(u32_t target) -> u8_t { return glIsBuffer(target); }

auto OGLGenericBufferHelper::ARB_isBuffer(u32_t target) -> u8_t { return OpenGLBufferExtension::glIsBufferARB(target); }

void OGLGenericBufferHelper::EMU_GetBufferParam(
    [[maybe_unused]] u32_t target, [[maybe_unused]] u32_t pname, [[maybe_unused]] s32_t *params) {}

void OGLGenericBufferHelper::STD_GetBufferParam(u32_t target, u32_t pname, s32_t *params) {
  return glGetBufferParameteriv(target, pname, params);
}

void OGLGenericBufferHelper::ARB_GetBufferParam(u32_t target, u32_t pname, s32_t *params) {
  return OpenGLBufferExtension::glGetBufferParameterivARB(target, pname, params);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
