#ifndef SWAY_GAPI_GL_WRAP_OGLSTATEHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLSTATEHELPER_HPP

#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLStateHelper {
public:
  OGLStateHelper();

  DECLARE_GENERIC_MEMBER(void, OGLStateHelper, blendFuncSeparate, u32_t, u32_t, u32_t, u32_t)
  void EMU_BlendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha);
  void STD_BlendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha);
  void EXT_BlendFuncSeparate(u32_t sfactorRGB, u32_t dfactorRGB, u32_t sfactorAlpha, u32_t dfactorAlpha);

  DECLARE_GENERIC_MEMBER(void, OGLStateHelper, blendEquationSeparate, u32_t, u32_t)
  void EMU_BlendEquationSeparate(u32_t rgb, u32_t alpha);
  void STD_BlendEquationSeparate(u32_t rgb, u32_t alpha);
  void EXT_BlendEquationSeparate(u32_t rgb, u32_t alpha);
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_WRAP_OGLSTATEHELPER_HPP
