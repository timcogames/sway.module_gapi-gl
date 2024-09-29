#include <sway/gapi/gl/oglbuffertargetconvertor.hpp>
#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglbufferextension.hpp>
#include <sway/gapi/gl/wrap/oglgenericbufferhelper.hpp>

// #define GL_GLEXT_PROTOTYPES 1
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

  flush_ = &OGLGenericBufferHelper::STD_FlushMappedBufferRange;

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_vertex_buffer_object")) {
    generateBuffers_ = &OGLGenericBufferHelper::ARB_GenerateBuffers;
    deleteBuffers_ = &OGLGenericBufferHelper::ARB_DeleteBuffers;
    bindBuffer_ = &OGLGenericBufferHelper::ARB_BindBuffer;
    bufferData_ = &OGLGenericBufferHelper::ARB_BufferData;
    bufferSubData_ = &OGLGenericBufferHelper::ARB_BufferSubData;
    isBuffer_ = &OGLGenericBufferHelper::ARB_IsBuffer;
    getBufferParam_ = &OGLGenericBufferHelper::ARB_GetBufferParam;
  } else {
    generateBuffers_ = &OGLGenericBufferHelper::STD_GenerateBuffers;
    deleteBuffers_ = &OGLGenericBufferHelper::STD_DeleteBuffers;
    bindBuffer_ = &OGLGenericBufferHelper::STD_BindBuffer;
    bufferData_ = &OGLGenericBufferHelper::STD_BufferData;
    bufferSubData_ = &OGLGenericBufferHelper::STD_BufferSubData;
    isBuffer_ = &OGLGenericBufferHelper::STD_IsBuffer;
    getBufferParam_ = &OGLGenericBufferHelper::STD_GetBufferParam;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_OES_mapbuffer")) {
    mapBuffer_ = &OGLGenericBufferHelper::OES_MapBuffer;
    unmapBuffer_ = &OGLGenericBufferHelper::OES_UnmapBuffer;
  } else if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_vertex_buffer_object")) {
    mapBuffer_ = &OGLGenericBufferHelper::ARB_MapBuffer;
    unmapBuffer_ = &OGLGenericBufferHelper::ARB_UnmapBuffer;
  } else {
    mapBuffer_ = &OGLGenericBufferHelper::STD_MapBuffer;
    unmapBuffer_ = &OGLGenericBufferHelper::STD_UnmapBuffer;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_transform_feedback")) {
    bindBufferRange_ = &OGLGenericBufferHelper::EXT_BindBufferRange;
  } else {
    bindBufferRange_ = &OGLGenericBufferHelper::STD_BindBufferRange;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_map_buffer_range")) {
    mapBufferRange_ = &OGLGenericBufferHelper::EXT_MapBufferRange;
  } else {
    mapBufferRange_ = &OGLGenericBufferHelper::STD_MapBufferRange;
  }
#endif
}

void OGLGenericBufferHelper::EMU_GenerateBuffers(u32_t latest, u32_t num, u32_t *uids) {
  for (auto i = 0; i < (i32_t)num; ++i) {
    uids[i] = i + latest + 1;
  }
}

void OGLGenericBufferHelper::STD_GenerateBuffers([[maybe_unused]] u32_t latest, u32_t num, u32_t *uids) {
  glGenBuffers(num, uids);
}

void OGLGenericBufferHelper::ARB_GenerateBuffers([[maybe_unused]] u32_t latest, u32_t num, u32_t *uids) {
  OGLBufferExtension::glGenBuffersARB(num, uids);
}

void OGLGenericBufferHelper::EMU_DeleteBuffers([[maybe_unused]] u32_t num, [[maybe_unused]] u32_t *uids) {}

void OGLGenericBufferHelper::STD_DeleteBuffers(u32_t num, u32_t *uids) { glDeleteBuffers(num, uids); }

void OGLGenericBufferHelper::ARB_DeleteBuffers(u32_t num, u32_t *uids) {
  OGLBufferExtension::glDeleteBuffersARB(num, uids);
}

void OGLGenericBufferHelper::EMU_BindBuffer(
    [[maybe_unused]] BufferTarget target, [[maybe_unused]] std::optional<u32_t> uid) {}

void OGLGenericBufferHelper::STD_BindBuffer(BufferTarget target, std::optional<u32_t> uid) {
  glBindBuffer(OGLBufferTargetConvertor::toGLenum(target), uid.value());
}

void OGLGenericBufferHelper::ARB_BindBuffer(BufferTarget target, std::optional<u32_t> uid) {
  OGLBufferExtension::glBindBufferARB(OGLBufferTargetConvertor::toGLenum(target), uid.value());
}

void OGLGenericBufferHelper::STD_BindBufferRange(
    BufferTarget target, std::optional<u32_t> uid, u32_t buf, ptrdiff_t offset, ptrdiff_t size) {
  glBindBufferRange(OGLBufferTargetConvertor::toGLenum(target), uid.value(), buf, offset, size);
}

void OGLGenericBufferHelper::EXT_BindBufferRange(
    BufferTarget target, std::optional<u32_t> uid, u32_t buf, ptrdiff_t offset, ptrdiff_t size) {
  OGLBufferExtension::glBindBufferRangeEXT(OGLBufferTargetConvertor::toGLenum(target), uid.value(), buf, offset, size);
}

void OGLGenericBufferHelper::EMU_BufferData([[maybe_unused]] BufferTarget target, [[maybe_unused]] ptrdiff_t size,
    [[maybe_unused]] const void *data, [[maybe_unused]] u32_t usage) {}

void OGLGenericBufferHelper::STD_BufferData(BufferTarget target, ptrdiff_t size, const void *data, u32_t usage) {
  glBufferData(OGLBufferTargetConvertor::toGLenum(target), size, data, usage);
}

void OGLGenericBufferHelper::ARB_BufferData(BufferTarget target, ptrdiff_t size, const void *data, u32_t usage) {
  OGLBufferExtension::glBufferDataARB(OGLBufferTargetConvertor::toGLenum(target), size, data, usage);
}

void OGLGenericBufferHelper::EMU_BufferSubData([[maybe_unused]] BufferTarget target, [[maybe_unused]] ptrdiff_t offset,
    [[maybe_unused]] ptrdiff_t size, [[maybe_unused]] const void *data) {}

void OGLGenericBufferHelper::STD_BufferSubData(
    BufferTarget target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  glBufferSubData(OGLBufferTargetConvertor::toGLenum(target), offset, size, data);
}

void OGLGenericBufferHelper::ARB_BufferSubData(
    BufferTarget target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  OGLBufferExtension::glBufferSubDataARB(OGLBufferTargetConvertor::toGLenum(target), offset, size, data);
}

void OGLGenericBufferHelper::STD_FlushMappedBufferRange(BufferTarget target, ptrdiff_t offset, ptrdiff_t length) {
  glFlushMappedBufferRange(OGLBufferTargetConvertor::toGLenum(target), offset, length);
}

auto OGLGenericBufferHelper::EMU_MapBuffer(
    [[maybe_unused]] BufferTarget target, [[maybe_unused]] u32_t access) -> void * {
  return nullptr;
}

auto OGLGenericBufferHelper::STD_MapBuffer(
    [[maybe_unused]] BufferTarget target, [[maybe_unused]] u32_t access) -> void * {
  // return glMapBuffer(OGLBufferTargetConvertor::toGLenum(target), access);
  std::cout << "[WARN] STD_MapBuffer" << std::endl;
  return nullptr;
}

auto OGLGenericBufferHelper::ARB_MapBuffer(BufferTarget target, u32_t access) -> void * {
  return OGLBufferExtension::glMapBufferARB(OGLBufferTargetConvertor::toGLenum(target), access);
}

auto OGLGenericBufferHelper::OES_MapBuffer(BufferTarget target, u32_t access) -> void * {
  return OGLBufferExtension::glMapBufferOES(OGLBufferTargetConvertor::toGLenum(target), access);
}

auto OGLGenericBufferHelper::EMU_MapBufferRange([[maybe_unused]] BufferTarget target, [[maybe_unused]] i32_t offset,
    [[maybe_unused]] i32_t length, [[maybe_unused]] u32_t access) -> void * {
  return nullptr;
}

auto OGLGenericBufferHelper::STD_MapBufferRange([[maybe_unused]] BufferTarget target, [[maybe_unused]] i32_t offset,
    [[maybe_unused]] i32_t length, [[maybe_unused]] u32_t access) -> void * {
  return glMapBufferRange(OGLBufferTargetConvertor::toGLenum(target), offset, length, access);
}

auto OGLGenericBufferHelper::EXT_MapBufferRange(
    BufferTarget target, i32_t offset, i32_t length, u32_t access) -> void * {
  return OGLBufferExtension::glMapBufferRangeEXT(OGLBufferTargetConvertor::toGLenum(target), offset, length, access);
}

auto OGLGenericBufferHelper::EMU_UnmapBuffer([[maybe_unused]] BufferTarget target) -> u8_t { return GL_TRUE; }

auto OGLGenericBufferHelper::STD_UnmapBuffer([[maybe_unused]] BufferTarget target) -> u8_t {
  return glUnmapBuffer(OGLBufferTargetConvertor::toGLenum(target));
}

auto OGLGenericBufferHelper::ARB_UnmapBuffer(BufferTarget target) -> u8_t {
  return OGLBufferExtension::glUnmapBufferARB(OGLBufferTargetConvertor::toGLenum(target));
}

auto OGLGenericBufferHelper::OES_UnmapBuffer(BufferTarget target) -> u8_t {
  return OGLBufferExtension::glUnmapBufferOES(OGLBufferTargetConvertor::toGLenum(target));
}

auto OGLGenericBufferHelper::EMU_IsBuffer([[maybe_unused]] std::optional<u32_t> uid) -> u8_t { return GL_TRUE; }

auto OGLGenericBufferHelper::STD_IsBuffer(std::optional<u32_t> uid) -> u8_t { return glIsBuffer(uid.value()); }

auto OGLGenericBufferHelper::ARB_IsBuffer(std::optional<u32_t> uid) -> u8_t {
  return OGLBufferExtension::glIsBufferARB(uid.value());
}

void OGLGenericBufferHelper::EMU_GetBufferParam(
    [[maybe_unused]] BufferTarget target, [[maybe_unused]] u32_t pname, [[maybe_unused]] i32_t *params) {}

void OGLGenericBufferHelper::STD_GetBufferParam(BufferTarget target, u32_t pname, i32_t *params) {
  glGetBufferParameteriv(OGLBufferTargetConvertor::toGLenum(target), pname, params);
}

void OGLGenericBufferHelper::ARB_GetBufferParam(BufferTarget target, u32_t pname, i32_t *params) {
  OGLBufferExtension::glGetBufferParameterivARB(OGLBufferTargetConvertor::toGLenum(target), pname, params);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
