#include <sway/gapi/gl/oglblendfunctionconvertor.hpp>
#include <sway/gapi/gl/oglcomparefunctionconvertor.hpp>
#include <sway/gapi/gl/oglstatecapabilityconvertor.hpp>
#include <sway/gapi/gl/oglstatecontext.hpp>
#include <sway/gapi/gl/oglstenciloperationconvertor.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLStateContext::createInstance() -> StateContextRef_t {
  auto instance = std::make_shared<OGLStateContext>();
  return instance;
}

OGLStateContext::OGLStateContext() {}

void OGLStateContext::setCapabilityEnable(StateCapability cap, bool enable) {
  (enable ? glEnable : glDisable)(OGLStateCapabilityConvertor::toGLenum(cap));
}

void OGLStateContext::setBlendEnable(bool enable) { setCapabilityEnable(StateCapability::BLEND, enable); }

void OGLStateContext::setBlendFn(BlendFn src, BlendFn dst) {
  glBlendFunc(OGLBlendFunctionConvertor::toGLenum(src), OGLBlendFunctionConvertor::toGLenum(dst));
}

void OGLStateContext::setDepthEnable(bool enable) { setCapabilityEnable(StateCapability::DEPTH_TEST, enable); }

void OGLStateContext::setDepthFn(CompareFn func) { glDepthFunc(OGLCompareFunctionConvertor::toGLenum(func)); }

void OGLStateContext::setDepthMask(bool flag) { glDepthMask(flag ? GL_TRUE : GL_FALSE); }

void OGLStateContext::setColorMask(bool red, bool green, bool blue, bool alpha) {
  glColorMask(red, green, blue, alpha);
}

void OGLStateContext::setStencilEnable(bool enable) { setCapabilityEnable(StateCapability::STENCIL_TEST, enable); }

void OGLStateContext::setStencilMask(u32_t mask) { glStencilMask(mask); }

void OGLStateContext::setStencilFn(CompareFn func, s32_t ref, u32_t mask) {
  glStencilFunc(OGLCompareFunctionConvertor::toGLenum(func), ref, mask);
}

void OGLStateContext::setStencilOp(gapi::StencilOp fail, gapi::StencilOp depthFail, gapi::StencilOp depthPass) {
  glStencilOp(OGLStencilOperationConvertor::toGLenum(fail), OGLStencilOperationConvertor::toGLenum(depthFail),
      OGLStencilOperationConvertor::toGLenum(depthPass));
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
