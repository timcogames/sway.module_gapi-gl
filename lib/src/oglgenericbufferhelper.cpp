#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/oglgenericbufferhelper.hpp>

#define GL_GLEXT_PROTOTYPES 1
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLGenericBufferHelper::OGLGenericBufferHelper(std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> exts)
    : extensions_(std::move(exts)) {
#ifdef _STUB
  GenerateBuffers_ = &OGLGenericBufferHelper::EMU_GenerateBuffers;
  DeleteBuffers_ = &OGLGenericBufferHelper::EMU_DeleteBuffers;
  BindBuffer_ = &OGLGenericBufferHelper::EMU_BindBuffer;
  BufferData_ = &OGLGenericBufferHelper::EMU_BufferData;
  BufferSubData_ = &OGLGenericBufferHelper::EMU_BufferSubData;
  IsBuffer_ = &OGLGenericBufferHelper::EMU_IsBuffer;
  GetBufferParam_ = &OGLGenericBufferHelper::EMU_GetBufferParam;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_vertex_buffer_object")) {
    GenerateBuffers_ = &OGLGenericBufferHelper::ARB_GenerateBuffers;
    DeleteBuffers_ = &OGLGenericBufferHelper::ARB_DeleteBuffers;
    BindBuffer_ = &OGLGenericBufferHelper::ARB_BindBuffer;
    BufferData_ = &OGLGenericBufferHelper::ARB_BufferData;
    BufferSubData_ = &OGLGenericBufferHelper::ARB_BufferSubData;
    IsBuffer_ = &OGLGenericBufferHelper::ARB_IsBuffer;
    GetBufferParam_ = &OGLGenericBufferHelper::ARB_GetBufferParam;
  } else {
    GenerateBuffers_ = &OGLGenericBufferHelper::STD_GenerateBuffers;
    DeleteBuffers_ = &OGLGenericBufferHelper::STD_DeleteBuffers;
    BindBuffer_ = &OGLGenericBufferHelper::STD_BindBuffer;
    BufferData_ = &OGLGenericBufferHelper::STD_BufferData;
    BufferSubData_ = &OGLGenericBufferHelper::STD_BufferSubData;
    IsBuffer_ = &OGLGenericBufferHelper::STD_IsBuffer;
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
  // core::binding::TFunction<u32_t(u32_t, u32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glGenBuffersARB"}});

  // callbackFunc(num, ids);

  Extension::glGenBuffers(num, ids);
}

void OGLGenericBufferHelper::EMU_DeleteBuffers([[maybe_unused]] u32_t num, [[maybe_unused]] u32_t *ids) {}

void OGLGenericBufferHelper::STD_DeleteBuffers(u32_t num, u32_t *ids) { glDeleteBuffers(num, ids); }

void OGLGenericBufferHelper::ARB_DeleteBuffers(u32_t num, u32_t *ids) {
  // core::binding::TFunction<u32_t(u32_t, u32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glDeleteBuffersARB"}});

  // callbackFunc(num, ids);

  Extension::glDeleteBuffers(num, ids);
}

void OGLGenericBufferHelper::EMU_BindBuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t buffer) {}

void OGLGenericBufferHelper::STD_BindBuffer(u32_t target, u32_t buffer) { glBindBuffer(target, buffer); }

void OGLGenericBufferHelper::ARB_BindBuffer(u32_t target, u32_t buffer) {
  // core::binding::TFunction<void(u32_t, u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glBindBufferARB"}});

  // callbackFunc(target, buffer);

  Extension::glBindBuffer(target, buffer);
}

void OGLGenericBufferHelper::EMU_BufferData([[maybe_unused]] u32_t target, [[maybe_unused]] ptrdiff_t size,
    [[maybe_unused]] const void *data, [[maybe_unused]] u32_t usage) {}

void OGLGenericBufferHelper::STD_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage) {
  glBufferData(target, size, data, usage);
}

void OGLGenericBufferHelper::ARB_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage) {
  // core::binding::TFunction<void(u32_t, ptrdiff_t, const void *, u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glBufferDataARB"}});

  // callbackFunc(target, size, data, usage);

  Extension::glBufferData(target, size, data, usage);
}

void OGLGenericBufferHelper::EMU_BufferSubData([[maybe_unused]] u32_t target, [[maybe_unused]] ptrdiff_t offset,
    [[maybe_unused]] ptrdiff_t size, [[maybe_unused]] const void *data) {}

void OGLGenericBufferHelper::STD_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  glBufferSubData(target, offset, size, data);
}

void OGLGenericBufferHelper::ARB_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  // core::binding::TFunction<void(u32_t, ptrdiff_t, ptrdiff_t, const void *)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glBufferSubDataARB"}});

  // callbackFunc(target, offset, size, data);

  Extension::glBufferSubData(target, offset, size, data);
}

auto OGLGenericBufferHelper::EMU_IsBuffer([[maybe_unused]] u32_t target) -> u8_t { return true; }

auto OGLGenericBufferHelper::STD_IsBuffer(u32_t target) -> u8_t { return glIsBuffer(target); }

auto OGLGenericBufferHelper::ARB_IsBuffer(u32_t target) -> u8_t {
  // core::binding::TFunction<u8_t(u32_t)> callbackFunc = extensions_({{"GL_ARB_vertex_buffer_object",
  // "glIsBufferARB"}});

  // return callbackFunc(target);

  return Extension::glIsBuffer(target);
}

void OGLGenericBufferHelper::EMU_GetBufferParam(
    [[maybe_unused]] u32_t target, [[maybe_unused]] u32_t pname, [[maybe_unused]] s32_t *params) {}

void OGLGenericBufferHelper::STD_GetBufferParam(u32_t target, u32_t pname, s32_t *params) {
  return glGetBufferParameteriv(target, pname, params);
}

void OGLGenericBufferHelper::ARB_GetBufferParam(u32_t target, u32_t pname, s32_t *params) {
  // core::binding::TFunction<void(u32_t, u32_t, s32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glGetBufferParameterivARB"}});

  // return callbackFunc(target, pname, params);

  return Extension::glGetBufferParameteriv(target, pname, params);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
