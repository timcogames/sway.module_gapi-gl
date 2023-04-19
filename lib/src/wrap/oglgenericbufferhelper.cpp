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
  generateBuffers_ = &OGLGenericBufferHelper::EMU_generateBuffers;
  deleteBuffers_ = &OGLGenericBufferHelper::EMU_deleteBuffers;
  bindBuffer_ = &OGLGenericBufferHelper::EMU_bindBuffer;
  bufferData_ = &OGLGenericBufferHelper::EMU_bufferData;
  bufferSubData_ = &OGLGenericBufferHelper::EMU_bufferSubData;
  mapBuffer_ = &OGLGenericBufferHelper::EMU_mapBuffer;
  mapBufferRange_ = &OGLGenericBufferHelper::EMU_mapBufferRange;
  unmapBuffer_ = &OGLGenericBufferHelper::EMU_unmapBuffer;
  isBuffer_ = &OGLGenericBufferHelper::EMU_isBuffer;
  getBufferParam_ = &OGLGenericBufferHelper::EMU_getBufferParam;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_vertex_buffer_object")) {
    generateBuffers_ = &OGLGenericBufferHelper::ARB_generateBuffers;
    deleteBuffers_ = &OGLGenericBufferHelper::ARB_deleteBuffers;
    bindBuffer_ = &OGLGenericBufferHelper::ARB_bindBuffer;
    bufferData_ = &OGLGenericBufferHelper::ARB_bufferData;
    bufferSubData_ = &OGLGenericBufferHelper::ARB_bufferSubData;
    mapBuffer_ = &OGLGenericBufferHelper::ARB_mapBuffer;
    unmapBuffer_ = &OGLGenericBufferHelper::ARB_unmapBuffer;
    isBuffer_ = &OGLGenericBufferHelper::ARB_isBuffer;
    getBufferParam_ = &OGLGenericBufferHelper::ARB_getBufferParam;
  } else {
    generateBuffers_ = &OGLGenericBufferHelper::STD_generateBuffers;
    deleteBuffers_ = &OGLGenericBufferHelper::STD_deleteBuffers;
    bindBuffer_ = &OGLGenericBufferHelper::STD_bindBuffer;
    bufferData_ = &OGLGenericBufferHelper::STD_bufferData;
    bufferSubData_ = &OGLGenericBufferHelper::STD_bufferSubData;
    mapBuffer_ = &OGLGenericBufferHelper::STD_mapBuffer;
    unmapBuffer_ = &OGLGenericBufferHelper::STD_unmapBuffer;
    isBuffer_ = &OGLGenericBufferHelper::STD_isBuffer;
    getBufferParam_ = &OGLGenericBufferHelper::STD_getBufferParam;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_map_buffer_range")) {
    mapBufferRange_ = &OGLGenericBufferHelper::EXT_mapBufferRange;
  } else {
    mapBufferRange_ = &OGLGenericBufferHelper::STD_mapBufferRange;
  }

#endif
}

void OGLGenericBufferHelper::EMU_generateBuffers(u32_t latest, u32_t num, u32_t *ids) {
  for (auto i = 0; i < (s32_t)num; ++i) {
    ids[i] = i + latest + 1;
  }
}

void OGLGenericBufferHelper::STD_generateBuffers([[maybe_unused]] u32_t latest, u32_t num, u32_t *ids) {
  glGenBuffers(num, ids);
}

void OGLGenericBufferHelper::ARB_generateBuffers([[maybe_unused]] u32_t latest, u32_t num, u32_t *ids) {
  OGLBufferExtension::glGenBuffersARB(num, ids);
}

void OGLGenericBufferHelper::EMU_deleteBuffers([[maybe_unused]] u32_t num, [[maybe_unused]] u32_t *ids) {}

void OGLGenericBufferHelper::STD_deleteBuffers(u32_t num, u32_t *ids) { glDeleteBuffers(num, ids); }

void OGLGenericBufferHelper::ARB_deleteBuffers(u32_t num, u32_t *ids) {
  OGLBufferExtension::glDeleteBuffersARB(num, ids);
}

void OGLGenericBufferHelper::EMU_bindBuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t buffer) {}

void OGLGenericBufferHelper::STD_bindBuffer(u32_t target, u32_t buffer) { glBindBuffer(target, buffer); }

void OGLGenericBufferHelper::ARB_bindBuffer(u32_t target, u32_t buffer) {
  OGLBufferExtension::glBindBufferARB(target, buffer);
}

void OGLGenericBufferHelper::EMU_bufferData([[maybe_unused]] u32_t target, [[maybe_unused]] ptrdiff_t size,
    [[maybe_unused]] const void *data, [[maybe_unused]] u32_t usage) {}

void OGLGenericBufferHelper::STD_bufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage) {
  glBufferData(target, size, data, usage);
}

void OGLGenericBufferHelper::ARB_bufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage) {
  OGLBufferExtension::glBufferDataARB(target, size, data, usage);
}

void OGLGenericBufferHelper::EMU_bufferSubData([[maybe_unused]] u32_t target, [[maybe_unused]] ptrdiff_t offset,
    [[maybe_unused]] ptrdiff_t size, [[maybe_unused]] const void *data) {}

void OGLGenericBufferHelper::STD_bufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  glBufferSubData(target, offset, size, data);
}

void OGLGenericBufferHelper::ARB_bufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  OGLBufferExtension::glBufferSubDataARB(target, offset, size, data);
}

auto OGLGenericBufferHelper::EMU_mapBuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t access) -> void * {
  return nullptr;
}

auto OGLGenericBufferHelper::STD_mapBuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t access) -> void * {
  // GL_OES_mapbuffer -> glMapBufferOES
  return nullptr;  // glMapBuffer(target, access);
}

auto OGLGenericBufferHelper::ARB_mapBuffer(u32_t target, u32_t access) -> void * {
  return OGLBufferExtension::glMapBufferARB(target, access);
}

auto OGLGenericBufferHelper::EMU_mapBufferRange([[maybe_unused]] u32_t target, [[maybe_unused]] s32_t offset,
    [[maybe_unused]] s32_t length, [[maybe_unused]] u32_t access) -> void * {
  return nullptr;
}

auto OGLGenericBufferHelper::STD_mapBufferRange([[maybe_unused]] u32_t target, [[maybe_unused]] s32_t offset,
    [[maybe_unused]] s32_t length, [[maybe_unused]] u32_t access) -> void * {
  return nullptr;  // glMapBufferRange(target, offset, length, access);
}

auto OGLGenericBufferHelper::EXT_mapBufferRange(u32_t target, s32_t offset, s32_t length, u32_t access) -> void * {
  return OGLBufferExtension::glMapBufferRangeEXT(target, offset, length, access);
}

auto OGLGenericBufferHelper::EMU_unmapBuffer([[maybe_unused]] u32_t target) -> u8_t { return GL_TRUE; }

auto OGLGenericBufferHelper::STD_unmapBuffer([[maybe_unused]] u32_t target) -> u8_t {
  // GL_OES_mapbuffer -> glUnmapBufferOES
  return GL_TRUE;  // glUnmapBuffer(target);
}

auto OGLGenericBufferHelper::ARB_unmapBuffer(u32_t target) -> u8_t {
  return OGLBufferExtension::glUnmapBufferARB(target);
}

auto OGLGenericBufferHelper::EMU_isBuffer([[maybe_unused]] u32_t target) -> u8_t { return GL_TRUE; }

auto OGLGenericBufferHelper::STD_isBuffer(u32_t target) -> u8_t { return glIsBuffer(target); }

auto OGLGenericBufferHelper::ARB_isBuffer(u32_t target) -> u8_t { return OGLBufferExtension::glIsBufferARB(target); }

void OGLGenericBufferHelper::EMU_getBufferParam(
    [[maybe_unused]] u32_t target, [[maybe_unused]] u32_t pname, [[maybe_unused]] s32_t *params) {}

void OGLGenericBufferHelper::STD_getBufferParam(u32_t target, u32_t pname, s32_t *params) {
  return glGetBufferParameteriv(target, pname, params);
}

void OGLGenericBufferHelper::ARB_getBufferParam(u32_t target, u32_t pname, s32_t *params) {
  return OGLBufferExtension::glGetBufferParameterivARB(target, pname, params);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
