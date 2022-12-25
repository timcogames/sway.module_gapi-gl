#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglvertexattriblayoutextension.hpp>
#include <sway/gapi/gl/wrap/oglvertexattriblayouthelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLVertexAttribLayoutHelper::OGLVertexAttribLayoutHelper() {
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
  OGLVertexAttribLayoutExtension::glEnableVertexAttribArrayARB(index);
}

void OGLVertexAttribLayoutHelper::EMU_DisableVertexAttribArray([[maybe_unused]] u32_t index) {}

void OGLVertexAttribLayoutHelper::STD_DisableVertexAttribArray(u32_t index) { glDisableVertexAttribArray(index); }

void OGLVertexAttribLayoutHelper::ARB_DisableVertexAttribArray(u32_t index) {
  OGLVertexAttribLayoutExtension::glDisableVertexAttribArrayARB(index);
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
  OGLVertexAttribLayoutExtension::glVertexAttribPointerARB(index, size, type, normalized, stride, pointer);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
