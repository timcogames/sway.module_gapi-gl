#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglvertexarrayextension.hpp>
#include <sway/gapi/gl/wrap/oglvertexarrayhelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLVertexArrayHelper::OGLVertexArrayHelper() {
#ifdef _STUB
  generateVertexArrays_ = &OGLVertexArrayHelper::EMU_GenerateVertexArrays;
  deleteVertexArrays_ = &OGLVertexArrayHelper::EMU_DeleteVertexArrays;
  bindVertexArray_ = &OGLVertexArrayHelper::EMU_BindVertexArray;
  isVertexArray_ = &OGLVertexArrayHelper::EMU_IsVertexArray;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_APPLE_vertex_array_object")) {
    generateVertexArrays_ = &OGLVertexArrayHelper::APPLE_GenerateVertexArrays;
    deleteVertexArrays_ = &OGLVertexArrayHelper::APPLE_DeleteVertexArrays;
    bindVertexArray_ = &OGLVertexArrayHelper::APPLE_BindVertexArray;
    isVertexArray_ = &OGLVertexArrayHelper::APPLE_IsVertexArray;
  } else {
    generateVertexArrays_ = &OGLVertexArrayHelper::STD_GenerateVertexArrays;
    deleteVertexArrays_ = &OGLVertexArrayHelper::STD_DeleteVertexArrays;
    bindVertexArray_ = &OGLVertexArrayHelper::STD_BindVertexArray;
    isVertexArray_ = &OGLVertexArrayHelper::STD_IsVertexArray;
  }

#endif
}

void OGLVertexArrayHelper::EMU_GenerateVertexArrays([[maybe_unused]] s32_t nbr, [[maybe_unused]] u32_t *arrays) {}

void OGLVertexArrayHelper::STD_GenerateVertexArrays(s32_t nbr, u32_t *arrays) { glGenVertexArrays(nbr, arrays); }

void OGLVertexArrayHelper::APPLE_GenerateVertexArrays(s32_t nbr, u32_t *arrays) {
  //  glGenVertexArraysAPPLE(nbr, arrays);
}

void OGLVertexArrayHelper::EMU_DeleteVertexArrays([[maybe_unused]] s32_t nbr, [[maybe_unused]] const u32_t *arrays) {}

void OGLVertexArrayHelper::STD_DeleteVertexArrays(s32_t nbr, const u32_t *arrays) { glDeleteVertexArrays(nbr, arrays); }

void OGLVertexArrayHelper::APPLE_DeleteVertexArrays(s32_t nbr, const u32_t *arrays) {
  // glDeleteVertexArraysAPPLE(nbr, arrays);
}

void OGLVertexArrayHelper::EMU_BindVertexArray([[maybe_unused]] u32_t array) {}

void OGLVertexArrayHelper::STD_BindVertexArray(u32_t array) { glBindVertexArray(array); }

void OGLVertexArrayHelper::APPLE_BindVertexArray(u32_t array) {
  // glBindVertexArrayAPPLE(array);
}

auto OGLVertexArrayHelper::EMU_IsVertexArray([[maybe_unused]] u32_t array) -> bool { return true; }

auto OGLVertexArrayHelper::STD_IsVertexArray(u32_t array) -> bool { return glIsVertexArray(array); }

auto OGLVertexArrayHelper::APPLE_IsVertexArray(u32_t array) -> bool {
  // return glIsVertexArrayAPPLE(array);
  return true;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
