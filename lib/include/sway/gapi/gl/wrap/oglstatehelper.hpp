#ifndef SWAY_GAPI_GL_WRAP_OGLSTATEHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLSTATEHELPER_HPP

#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLStateHelper {
public:
  OGLStateHelper();

  DECLARE_GENERIC_MEMBER(void, OGLStateHelper, blendFuncSeparate, u32_t, u32_t, u32_t, u32_t)
  void EMU_blendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha);
  void STD_blendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha);
  void EXT_blendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha);

  DECLARE_GENERIC_MEMBER(void, OGLStateHelper, blendFuncSeparateI, u32_t, u32_t, u32_t, u32_t, u32_t)
  void EMU_blendFuncSeparateI(u32_t buf, u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha);
  void STD_blendFuncSeparateI(u32_t buf, u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha);
  void ARB_blendFuncSeparateI(u32_t buf, u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha);

  DECLARE_GENERIC_MEMBER(void, OGLStateHelper, blendEquationSeparate, u32_t, u32_t)
  void EMU_blendEquationSeparate(u32_t rgb, u32_t alpha);
  void STD_blendEquationSeparate(u32_t rgb, u32_t alpha);
  void EXT_blendEquationSeparate(u32_t rgb, u32_t alpha);

  DECLARE_GENERIC_MEMBER(void, OGLStateHelper, blendEquationSeparateI, u32_t, u32_t, u32_t)
  void EMU_blendEquationSeparateI(u32_t buf, u32_t rgb, u32_t alpha);
  void STD_blendEquationSeparateI(u32_t buf, u32_t rgb, u32_t alpha);
  void ARB_blendEquationSeparateI(u32_t buf, u32_t rgb, u32_t alpha);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLSTATEHELPER_HPP
