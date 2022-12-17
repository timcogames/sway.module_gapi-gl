#include <sway/gapi/gl/bufferhelper.hpp>
#include <sway/gapi/gl/capability.hpp>
#include <sway/gapi/gl/extensions.hpp>

#define GL_GLEXT_PROTOTYPES 1
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

BufferHelper::BufferHelper(std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> exts)
    : extensions_(std::move(exts)) {
#ifdef _TESTS
  GenerateBuffers_ = &BufferHelper::EMU_GenerateBuffers;
  DeleteBuffers_ = &BufferHelper::EMU_DeleteBuffers;
  BindBuffer_ = &BufferHelper::EMU_BindBuffer;
  BufferData_ = &BufferHelper::EMU_BufferData;
  BufferSubData_ = &BufferHelper::EMU_BufferSubData;
  IsBuffer_ = &BufferHelper::EMU_IsBuffer;
  GetBufferParam_ = &BufferHelper::EMU_GetBufferParam;
#else

  const auto *extensions = Capability::getExtensions();
  if (Capability::isExtensionSupported(extensions, "GL_ARB_vertex_buffer_object")) {
    GenerateBuffers_ = &BufferHelper::ARB_GenerateBuffers;
    DeleteBuffers_ = &BufferHelper::ARB_DeleteBuffers;
    BindBuffer_ = &BufferHelper::ARB_BindBuffer;
    BufferData_ = &BufferHelper::ARB_BufferData;
    BufferSubData_ = &BufferHelper::ARB_BufferSubData;
    IsBuffer_ = &BufferHelper::ARB_IsBuffer;
    GetBufferParam_ = &BufferHelper::ARB_GetBufferParam;
  } else {
    GenerateBuffers_ = &BufferHelper::STD_GenerateBuffers;
    DeleteBuffers_ = &BufferHelper::STD_DeleteBuffers;
    BindBuffer_ = &BufferHelper::STD_BindBuffer;
    BufferData_ = &BufferHelper::STD_BufferData;
    BufferSubData_ = &BufferHelper::STD_BufferSubData;
    IsBuffer_ = &BufferHelper::STD_IsBuffer;
    GetBufferParam_ = &BufferHelper::STD_GetBufferParam;
  }

#endif  // _TESTS
}

void BufferHelper::EMU_GenerateBuffers(u32_t latest, u32_t num, u32_t *ids) {
  for (auto i = 0; i < (s32_t)num; ++i) {
    ids[i] = i + latest + 1;
  }
}

void BufferHelper::STD_GenerateBuffers([[maybe_unused]] u32_t latest, u32_t num, u32_t *ids) { glGenBuffers(num, ids); }

void BufferHelper::ARB_GenerateBuffers([[maybe_unused]] u32_t latest, u32_t num, u32_t *ids) {
  // core::binding::TFunction<u32_t(u32_t, u32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glGenBuffersARB"}});

  // callbackFunc(num, ids);

  Extension::glGenBuffers(num, ids);
}

void BufferHelper::EMU_DeleteBuffers([[maybe_unused]] u32_t num, [[maybe_unused]] u32_t *ids) {}

void BufferHelper::STD_DeleteBuffers(u32_t num, u32_t *ids) { glDeleteBuffers(num, ids); }

void BufferHelper::ARB_DeleteBuffers(u32_t num, u32_t *ids) {
  // core::binding::TFunction<u32_t(u32_t, u32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glDeleteBuffersARB"}});

  // callbackFunc(num, ids);

  Extension::glDeleteBuffers(num, ids);
}

void BufferHelper::EMU_BindBuffer([[maybe_unused]] u32_t target, [[maybe_unused]] u32_t buffer) {}

void BufferHelper::STD_BindBuffer(u32_t target, u32_t buffer) { glBindBuffer(target, buffer); }

void BufferHelper::ARB_BindBuffer(u32_t target, u32_t buffer) {
  // core::binding::TFunction<void(u32_t, u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glBindBufferARB"}});

  // callbackFunc(target, buffer);

  Extension::glBindBuffer(target, buffer);
}

void BufferHelper::EMU_BufferData([[maybe_unused]] u32_t target, [[maybe_unused]] ptrdiff_t size,
    [[maybe_unused]] const void *data, [[maybe_unused]] u32_t usage) {}

void BufferHelper::STD_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage) {
  glBufferData(target, size, data, usage);
}

void BufferHelper::ARB_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage) {
  // core::binding::TFunction<void(u32_t, ptrdiff_t, const void *, u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glBufferDataARB"}});

  // callbackFunc(target, size, data, usage);

  Extension::glBufferData(target, size, data, usage);
}

void BufferHelper::EMU_BufferSubData([[maybe_unused]] u32_t target, [[maybe_unused]] ptrdiff_t offset,
    [[maybe_unused]] ptrdiff_t size, [[maybe_unused]] const void *data) {}

void BufferHelper::STD_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  glBufferSubData(target, offset, size, data);
}

void BufferHelper::ARB_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data) {
  // core::binding::TFunction<void(u32_t, ptrdiff_t, ptrdiff_t, const void *)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glBufferSubDataARB"}});

  // callbackFunc(target, offset, size, data);

  Extension::glBufferSubData(target, offset, size, data);
}

auto BufferHelper::EMU_IsBuffer([[maybe_unused]] u32_t target) -> u8_t { return true; }

auto BufferHelper::STD_IsBuffer(u32_t target) -> u8_t { return glIsBuffer(target); }

auto BufferHelper::ARB_IsBuffer(u32_t target) -> u8_t {
  // core::binding::TFunction<u8_t(u32_t)> callbackFunc = extensions_({{"GL_ARB_vertex_buffer_object",
  // "glIsBufferARB"}});

  // return callbackFunc(target);

  return Extension::glIsBuffer(target);
}

void BufferHelper::EMU_GetBufferParam(
    [[maybe_unused]] u32_t target, [[maybe_unused]] u32_t pname, [[maybe_unused]] s32_t *params) {}

void BufferHelper::STD_GetBufferParam(u32_t target, u32_t pname, s32_t *params) {
  return glGetBufferParameteriv(target, pname, params);
}

void BufferHelper::ARB_GetBufferParam(u32_t target, u32_t pname, s32_t *params) {
  // core::binding::TFunction<void(u32_t, u32_t, s32_t *)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_buffer_object", "glGetBufferParameterivARB"}});

  // return callbackFunc(target, pname, params);

  return Extension::glGetBufferParameteriv(target, pname, params);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
