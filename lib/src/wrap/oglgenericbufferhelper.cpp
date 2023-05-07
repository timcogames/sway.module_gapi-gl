#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglbufferextension.hpp>
#include <sway/gapi/gl/wrap/oglgenericbufferhelper.hpp>

#define GL_GLEXT_PROTOTYPES 1
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLGenericBufferHelper::OGLGenericBufferHelper() {
#ifdef _STUB
  generateBuffers_ = &OGLGenericBufferHelper::EMU_GenerateBuffers;
  deleteBuffers_ = &OGLGenericBufferHelper::EMU_DeleteBuffers;
  bindBuffer_ = &OGLGenericBufferHelper::EMU_BindBuffer;
  bufferData_ = &OGLGenericBufferHelper::EMU_BufferData;
  bufferSubData_ = &OGLGenericBufferHelper::EMU_BufferSubData;
  mapBuffer_ = &OGLGenericBufferHelper::EMU_MapBuffer;
  mapBufferRange_ = &OGLGenericBufferHelper::EMU_MapBufferRange;
  unmapBuffer_ = &OGLGenericBufferHelper::EMU_UnmapBuffer;
  isBuffer_ = &OGLGenericBufferHelper::EMU_IsBuffer;
  getBufferParam_ = &OGLGenericBufferHelper::EMU_GetBufferParam;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_vertex_buffer_object")) {
    generateBuffers_ = &OGLGenericBufferHelper::ARB_GenerateBuffers;
    deleteBuffers_ = &OGLGenericBufferHelper::ARB_DeleteBuffers;
    bindBuffer_ = &OGLGenericBufferHelper::ARB_BindBuffer;
    bufferData_ = &OGLGenericBufferHelper::ARB_BufferData;
    bufferSubData_ = &OGLGenericBufferHelper::ARB_BufferSubData;
    mapBuffer_ = &OGLGenericBufferHelper::ARB_MapBuffer;
    unmapBuffer_ = &OGLGenericBufferHelper::ARB_UnmapBuffer;
    isBuffer_ = &OGLGenericBufferHelper::ARB_IsBuffer;
    getBufferParam_ = &OGLGenericBufferHelper::ARB_GetBufferParam;
  } else {
    generateBuffers_ = &OGLGenericBufferHelper::STD_GenerateBuffers;
    deleteBuffers_ = &OGLGenericBufferHelper::STD_DeleteBuffers;
    bindBuffer_ = &OGLGenericBufferHelper::STD_BindBuffer;
    bufferData_ = &OGLGenericBufferHelper::STD_BufferData;
    bufferSubData_ = &OGLGenericBufferHelper::STD_BufferSubData;
    mapBuffer_ = &OGLGenericBufferHelper::STD_MapBuffer;
    unmapBuffer_ = &OGLGenericBufferHelper::STD_UnmapBuffer;
    isBuffer_ = &OGLGenericBufferHelper::STD_IsBuffer;
    getBufferParam_ = &OGLGenericBufferHelper::STD_GetBufferParam;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_map_buffer_range")) {
    mapBufferRange_ = &OGLGenericBufferHelper::EXT_MapBufferRange;
  } else {
    mapBufferRange_ = &OGLGenericBufferHelper::STD_MapBufferRange;
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
  OGLBufferExtension::glGenBuffersARB(num, ids);
}

void OGLGenericBufferHelper::EMU_DeleteBuffers([[maybe_unused]] u32_t num, [[maybe_unused]] u32_t *ids) {}

void OGLGenericBufferHelper::STD_DeleteBuffers(u32_t num, u32_t *ids) { glDeleteBuffers(num, ids); }

void OGLGenericBufferHelper::ARB_DeleteBuffers(u32_t num, u32_t *ids) {
  OGLBufferExtension::glDeleteBuffersARB(num, ids);
}

void OGLGenericBufferHelper::EMU_BindBuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t buffer) {}

void OGLGenericBufferHelper::STD_BindBuffer(u32_t target, u32_t buffer) { glBindBuffer(target, buffer); }

void OGLGenericBufferHelper::ARB_BindBuffer(u32_t target, u32_t buffer) {
  OGLBufferExtension::glBindBufferARB(target, buffer);
}

void OGLGenericBufferHelper::EMU_BufferData([[maybe_unused]] u32_t target, [[maybe_unused]] ptrdiff_t size,
    [[maybe_unused]] const void *data, [[maybe_unused]] u32_t usage) {}

void OGLGenericBufferHelper::STD_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage) {
  glBufferData(target, size, data, usage);
}

void OGLGenericBufferHelper::ARB_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage) {
  OGLBufferExtension::glBufferDataARB(target, size, data, usage);
}

void OGLGenericBufferHelper::EMU_BufferSubData([[maybe_unused]] u32_t target, [[maybe_unused]] ptrdiff_t offset,
    [[maybe_unused]] ptrdiff_t size, [[maybe_unused]] const void *data) {}

void OGLGenericBufferHelper::STD_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  glBufferSubData(target, offset, size, data);
}

void OGLGenericBufferHelper::ARB_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  OGLBufferExtension::glBufferSubDataARB(target, offset, size, data);
}

auto OGLGenericBufferHelper::EMU_MapBuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t access) -> void * {
  return nullptr;
}

auto OGLGenericBufferHelper::STD_MapBuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t access) -> void * {
  // GL_OES_Mapbuffer -> glMapBufferOES
  return nullptr;  // glMapBuffer(target, access);
}

auto OGLGenericBufferHelper::ARB_MapBuffer(u32_t target, u32_t access) -> void * {
  return OGLBufferExtension::glMapBufferARB(target, access);
}

auto OGLGenericBufferHelper::EMU_MapBufferRange([[maybe_unused]] u32_t target, [[maybe_unused]] s32_t offset,
    [[maybe_unused]] s32_t length, [[maybe_unused]] u32_t access) -> void * {
  return nullptr;
}

auto OGLGenericBufferHelper::STD_MapBufferRange([[maybe_unused]] u32_t target, [[maybe_unused]] s32_t offset,
    [[maybe_unused]] s32_t length, [[maybe_unused]] u32_t access) -> void * {
  return nullptr;  // glMapBufferRange(target, offset, length, access);
}

auto OGLGenericBufferHelper::EXT_MapBufferRange(u32_t target, s32_t offset, s32_t length, u32_t access) -> void * {
  return OGLBufferExtension::glMapBufferRangeEXT(target, offset, length, access);
}

auto OGLGenericBufferHelper::EMU_UnmapBuffer([[maybe_unused]] u32_t target) -> u8_t { return GL_TRUE; }

auto OGLGenericBufferHelper::STD_UnmapBuffer([[maybe_unused]] u32_t target) -> u8_t {
  // GL_OES_Mapbuffer -> glUnmapBufferOES
  return GL_TRUE;  // glUnmapBuffer(target);
}

auto OGLGenericBufferHelper::ARB_UnmapBuffer(u32_t target) -> u8_t {
  return OGLBufferExtension::glUnmapBufferARB(target);
}

auto OGLGenericBufferHelper::EMU_IsBuffer([[maybe_unused]] u32_t target) -> u8_t { return GL_TRUE; }

auto OGLGenericBufferHelper::STD_IsBuffer(u32_t target) -> u8_t { return glIsBuffer(target); }

auto OGLGenericBufferHelper::ARB_IsBuffer(u32_t target) -> u8_t { return OGLBufferExtension::glIsBufferARB(target); }

void OGLGenericBufferHelper::EMU_GetBufferParam(
    [[maybe_unused]] u32_t target, [[maybe_unused]] u32_t pname, [[maybe_unused]] s32_t *params) {}

void OGLGenericBufferHelper::STD_GetBufferParam(u32_t target, u32_t pname, s32_t *params) {
  return glGetBufferParameteriv(target, pname, params);
}

void OGLGenericBufferHelper::ARB_GetBufferParam(u32_t target, u32_t pname, s32_t *params) {
  return OGLBufferExtension::glGetBufferParameterivARB(target, pname, params);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
