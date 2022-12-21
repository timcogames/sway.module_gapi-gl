#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/oglvertexattriblayouthelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLVertexAttribLayoutHelper::OGLVertexAttribLayoutHelper(
    std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> exts)
    : extensions_(std::move(exts)) {

#ifdef _STUB
  EnableArray_ = &OGLVertexAttribLayoutHelper::EMU_EnableVertexAttribArray;
  DisableArray_ = &OGLVertexAttribLayoutHelper::EMU_EnableVertexAttribArray;
  Setup_ = &OGLVertexAttribLayoutHelper::EMU_SetupVertexAttribPointer;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_ARB_vertex_program")) {
    EnableArray_ = &OGLVertexAttribLayoutHelper::ARB_EnableVertexAttribArray;
    DisableArray_ = &OGLVertexAttribLayoutHelper::ARB_EnableVertexAttribArray;
    Setup_ = &OGLVertexAttribLayoutHelper::ARB_SetupVertexAttribPointer;
  } else {
    EnableArray_ = &OGLVertexAttribLayoutHelper::STD_EnableVertexAttribArray;
    DisableArray_ = &OGLVertexAttribLayoutHelper::STD_EnableVertexAttribArray;
    Setup_ = &OGLVertexAttribLayoutHelper::STD_SetupVertexAttribPointer;
  }

#endif
}

void OGLVertexAttribLayoutHelper::EMU_EnableVertexAttribArray([[maybe_unused]] u32_t index) {}

void OGLVertexAttribLayoutHelper::STD_EnableVertexAttribArray(u32_t index) { glEnableVertexAttribArray(index); }

void OGLVertexAttribLayoutHelper::ARB_EnableVertexAttribArray(u32_t index) {
  // core::binding::TFunction<void(u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_program", "glEnableVertexAttribArrayARB"}});

  // callbackFunc(index);

  Extension::glEnableVertexAttribArray(index);
}

void OGLVertexAttribLayoutHelper::EMU_DisableVertexAttribArray([[maybe_unused]] u32_t index) {}

void OGLVertexAttribLayoutHelper::STD_DisableVertexAttribArray(u32_t index) { glDisableVertexAttribArray(index); }

void OGLVertexAttribLayoutHelper::ARB_DisableVertexAttribArray(u32_t index) {
  // core::binding::TFunction<void(u32_t)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_program", "glDisableVertexAttribArrayARB"}});

  // callbackFunc(index);

  Extension::glDisableVertexAttribArray(index);
}

void OGLVertexAttribLayoutHelper::EMU_SetupVertexAttribPointer([[maybe_unused]] u32_t index,
    [[maybe_unused]] s32_t size, [[maybe_unused]] u32_t type, [[maybe_unused]] u8_t normalized,
    [[maybe_unused]] s32_t stride, [[maybe_unused]] const void *pointer) {}

void OGLVertexAttribLayoutHelper::STD_SetupVertexAttribPointer(
    u32_t index, s32_t size, u32_t type, u8_t normalized, s32_t stride, const void *pointer) {
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void OGLVertexAttribLayoutHelper::ARB_SetupVertexAttribPointer(
    u32_t index, s32_t size, u32_t type, u8_t normalized, s32_t stride, const void *pointer) {
  // core::binding::TFunction<void(u32_t, s32_t, u32_t, u8_t, s32_t, const void *)> callbackFunc =
  //     extensions_({{"GL_ARB_vertex_program", "glVertexAttribPointerARB"}});

  // callbackFunc(index, size, type, normalized, stride, pointer);

  Extension::glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
