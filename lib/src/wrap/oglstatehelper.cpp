#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglstateextension.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

#include <GLES2/gl2.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLStateHelper::OGLStateHelper() {
#ifdef _STUB
  blendFuncSeparate_ = &OGLStateHelper::EMU_BlendFuncSeparate;
  blendEquationSeparate_ = &OGLStateHelper::EMU_BlendEquationSeparate;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_blend_func_separate")) {
    blendFuncSeparate_ = &OGLStateHelper::EXT_BlendFuncSeparate;
  } else {
    blendFuncSeparate_ = &OGLStateHelper::STD_BlendFuncSeparate;
  }

  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_blend_equation_separate")) {
    blendEquationSeparate_ = &OGLStateHelper::EXT_BlendEquationSeparate;
  } else {
    blendEquationSeparate_ = &OGLStateHelper::STD_BlendEquationSeparate;
  }

#endif
}

void OGLStateHelper::EMU_BlendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha) {
}

void OGLStateHelper::STD_BlendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha) {
  glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

void OGLStateHelper::EXT_BlendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha) {
  OGLStateExtension::glBlendFuncSeparateEXT(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

void OGLStateHelper::EMU_BlendEquationSeparate(u32_t rgb, u32_t alpha) {}

void OGLStateHelper::STD_BlendEquationSeparate(u32_t rgb, u32_t alpha) { glBlendEquationSeparate(rgb, alpha); }

void OGLStateHelper::EXT_BlendEquationSeparate(u32_t rgb, u32_t alpha) {
  OGLStateExtension::glBlendEquationSeparateEXT(rgb, alpha);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
