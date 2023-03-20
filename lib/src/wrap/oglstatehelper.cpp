#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglstateextension.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLStateHelper::OGLStateHelper() {
#ifdef _STUB
  blendFuncSeparate_ = &OGLStateHelper::EMU_blendFuncSeparate;
  blendEquationSeparate_ = &OGLStateHelper::EMU_blendEquationSeparate;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_blend_func_separate")) {
    blendFuncSeparate_ = &OGLStateHelper::EXT_blendFuncSeparate;
  } else {
    blendFuncSeparate_ = &OGLStateHelper::STD_blendFuncSeparate;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_blend_equation_separate")) {
    blendEquationSeparate_ = &OGLStateHelper::EXT_blendEquationSeparate;
  } else {
    blendEquationSeparate_ = &OGLStateHelper::STD_blendEquationSeparate;
  }

#endif
}

void OGLStateHelper::EMU_blendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha) {
}

void OGLStateHelper::STD_blendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha) {
  glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

void OGLStateHelper::EXT_blendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha) {
  OGLStateExtension::glBlendFuncSeparateEXT(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

void OGLStateHelper::EMU_blendEquationSeparate(u32_t rgb, u32_t alpha) {}

void OGLStateHelper::STD_blendEquationSeparate(u32_t rgb, u32_t alpha) { glBlendEquationSeparate(rgb, alpha); }

void OGLStateHelper::EXT_blendEquationSeparate(u32_t rgb, u32_t alpha) {
  OGLStateExtension::glBlendEquationSeparateEXT(rgb, alpha);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
