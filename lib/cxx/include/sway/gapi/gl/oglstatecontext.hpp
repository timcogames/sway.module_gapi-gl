#ifndef SWAY_GAPI_GL_OGLSTATECONTEXT_HPP
#define SWAY_GAPI_GL_OGLSTATECONTEXT_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLStateContext : public StateContext {
public:
  static auto createInstance() -> StateContextPtr_t;

  OGLStateContext();

  virtual ~OGLStateContext() = default;

  MTHD_OVERRIDE(void setCapabilityEnable(StateCapability cap, bool enable));

  MTHD_OVERRIDE(void setBlendEnable(bool enable));

  MTHD_OVERRIDE(void setBlendFn(BlendFn src, BlendFn dst));

  MTHD_OVERRIDE(void setDepthEnable(bool enable));

  MTHD_OVERRIDE(void setDepthFn(CompareFn func));

  MTHD_OVERRIDE(void setDepthMask(bool enable));

  MTHD_OVERRIDE(void setColorMask(bool red, bool green, bool blue, bool alpha));

  MTHD_OVERRIDE(void setStencilEnable(bool enable));

  MTHD_OVERRIDE(void setStencilMask(u32_t mask));

  MTHD_OVERRIDE(void setStencilFn(CompareFn func, s32_t ref, u32_t mask));

  MTHD_OVERRIDE(void setStencilOp(StencilOp fail, StencilOp depthFail, StencilOp depthPass));

  MTHD_OVERRIDE(void setPolygonMode(PolygonMode mode));

private:
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTATECONTEXT_HPP
