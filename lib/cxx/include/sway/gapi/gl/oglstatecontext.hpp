#ifndef SWAY_GAPI_GL_OGLSTATECONTEXT_HPP
#define SWAY_GAPI_GL_OGLSTATECONTEXT_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLStateContext : public StateContext {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance() -> StateContextPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  OGLStateContext();

  DTOR_VIRTUAL_DEFAULT(OGLStateContext);

#pragma endregion

#pragma region "Overridden StateContext methods"

  MTHD_OVERRIDE(void setCapabilityEnable(StateCapability::Enum cap, bool enable));

  MTHD_OVERRIDE(void setAlphaEnable(bool enable));

  MTHD_OVERRIDE(void setAlphaFunc(CompareFn::Enum func, f32_t ref));

  MTHD_OVERRIDE(void setBlendEnable(bool enable));

  MTHD_OVERRIDE(void setBlendFn(BlendFn::Enum src, BlendFn::Enum dst));

  MTHD_OVERRIDE(void setDepthEnable(bool enable));

  MTHD_OVERRIDE(void setClearDepth(f64_t depth));

  MTHD_OVERRIDE(void setDepthFn(CompareFn::Enum func));

  MTHD_OVERRIDE(void setDepthMask(bool enable));

  MTHD_OVERRIDE(void setColorMask(bool red, bool green, bool blue, bool alpha));

  MTHD_OVERRIDE(void setStencilEnable(bool enable));

  MTHD_OVERRIDE(void setClearStencil(i32_t idx));

  MTHD_OVERRIDE(void setStencilMask(u32_t mask));

  MTHD_OVERRIDE(void setStencilFn(CompareFn::Enum func, i32_t ref, u32_t mask));

  MTHD_OVERRIDE(void setStencilOp(StencilOp::Enum fail, StencilOp::Enum depthFail, StencilOp::Enum depthPass));

  MTHD_OVERRIDE(void setPolygonMode(PolygonMode::Enum mode));

#pragma endregion
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLSTATECONTEXT_HPP
