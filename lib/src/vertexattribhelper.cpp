#include <sway/gapi/gl/capability.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/vertexattribhelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

VertexAttribHelper::VertexAttribHelper(std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> exts)
    : extensions_(std::move(exts)) {

#ifdef _STUB
  EnableArray_ = &VertexAttribHelper::EMU_EnableVertexAttribArray;
  DisableArray_ = &VertexAttribHelper::EMU_EnableVertexAttribArray;
  Setup_ = &VertexAttribHelper::EMU_SetupVertexAttribPointer;
#else

  const auto *extensions = Capability::getExtensions();
  if (Capability::isExtensionSupported(extensions, "GL_ARB_vertex_program")) {
    EnableArray_ = &VertexAttribHelper::ARB_EnableVertexAttribArray;
    DisableArray_ = &VertexAttribHelper::ARB_EnableVertexAttribArray;
    Setup_ = &VertexAttribHelper::ARB_SetupVertexAttribPointer;
  } else {
    EnableArray_ = &VertexAttribHelper::STD_EnableVertexAttribArray;
    DisableArray_ = &VertexAttribHelper::STD_EnableVertexAttribArray;
    Setup_ = &VertexAttribHelper::STD_SetupVertexAttribPointer;
  }

#endif
}

void VertexAttribHelper::EMU_EnableVertexAttribArray([[maybe_unused]] u32_t index) {}

void VertexAttribHelper::STD_EnableVertexAttribArray(u32_t index) { glEnableVertexAttribArray(index); }

void VertexAttribHelper::ARB_EnableVertexAttribArray(u32_t index) {
  // core::binding::TFunction<void(u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_program", "glEnableVertexAttribArrayARB"}});

  // callbackFunc(index);

  Extension::glEnableVertexAttribArray(index);
}

void VertexAttribHelper::EMU_DisableVertexAttribArray([[maybe_unused]] u32_t index) {}

void VertexAttribHelper::STD_DisableVertexAttribArray(u32_t index) { glDisableVertexAttribArray(index); }

void VertexAttribHelper::ARB_DisableVertexAttribArray(u32_t index) {
  // core::binding::TFunction<void(u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_program", "glDisableVertexAttribArrayARB"}});

  // callbackFunc(index);

  Extension::glDisableVertexAttribArray(index);
}

void VertexAttribHelper::EMU_SetupVertexAttribPointer([[maybe_unused]] u32_t index, [[maybe_unused]] s32_t size,
    [[maybe_unused]] u32_t type, [[maybe_unused]] u8_t normalized, [[maybe_unused]] s32_t stride,
    [[maybe_unused]] const void *pointer) {}

void VertexAttribHelper::STD_SetupVertexAttribPointer(
    u32_t index, s32_t size, u32_t type, u8_t normalized, s32_t stride, const void *pointer) {
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexAttribHelper::ARB_SetupVertexAttribPointer(
    u32_t index, s32_t size, u32_t type, u8_t normalized, s32_t stride, const void *pointer) {
  // core::binding::TFunction<void(u32_t, s32_t, u32_t, u8_t, s32_t, const void *)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_program", "glVertexAttribPointerARB"}});

  // callbackFunc(index, size, type, normalized, stride, pointer);

  Extension::glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
