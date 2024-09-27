#include <sway/gapi/gl/oglblendfunctionconvertor.hpp>
#include <sway/gapi/gl/oglcomparefunctionconvertor.hpp>
#include <sway/gapi/gl/oglstatecapabilityconvertor.hpp>
#include <sway/gapi/gl/oglstatecontext.hpp>
#include <sway/gapi/gl/oglstenciloperationconvertor.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLStateContext::createInstance() -> StateContextPtr_t {
  auto *instance = new OGLStateContext();
  return instance;
}

OGLStateContext::OGLStateContext() {}

void OGLStateContext::setCapabilityEnable(StateCapability cap, bool enable) {
  (enable ? glEnable : glDisable)(OGLStateCapabilityConvertor::toGLenum(cap));
}

void OGLStateContext::setAlphaEnable(bool enable) { setCapabilityEnable(StateCapability::ALPHA_TEST, enable); }

void OGLStateContext::setAlphaFunc(CompareFn func, f32_t ref) {
  // glAlphaFunc(OGLCompareFunctionConvertor::toGLenum(func), ref);
  std::cout << "[setAlphaFunc]: Deprecated" << std::endl;
}

void OGLStateContext::setBlendEnable(bool enable) { setCapabilityEnable(StateCapability::BLEND, enable); }

void OGLStateContext::setBlendFn(BlendFn src, BlendFn dst) {
  glBlendFunc(OGLBlendFunctionConvertor::toGLenum(src), OGLBlendFunctionConvertor::toGLenum(dst));
}

void OGLStateContext::setDepthEnable(bool enable) { setCapabilityEnable(StateCapability::DEPTH_TEST, enable); }

void OGLStateContext::setClearDepth(f64_t depth) { glClearDepth(depth); }

void OGLStateContext::setDepthFn(CompareFn func) { glDepthFunc(OGLCompareFunctionConvertor::toGLenum(func)); }

void OGLStateContext::setDepthMask(bool flag) { glDepthMask(flag ? GL_TRUE : GL_FALSE); }

void OGLStateContext::setColorMask(bool red, bool green, bool blue, bool alpha) {
  glColorMask(red, green, blue, alpha);
}

void OGLStateContext::setStencilEnable(bool enable) { setCapabilityEnable(StateCapability::STENCIL_TEST, enable); }

void OGLStateContext::setClearStencil(i32_t idx) { glClearStencil(idx); }

void OGLStateContext::setStencilMask(u32_t mask) { glStencilMask(mask); }

void OGLStateContext::setStencilFn(CompareFn func, i32_t ref, u32_t mask) {
  glStencilFunc(OGLCompareFunctionConvertor::toGLenum(func), ref, mask);
}

void OGLStateContext::setStencilOp(StencilOp fail, StencilOp depthFail, StencilOp depthPass) {
  glStencilOp(OGLStencilOperationConvertor::toGLenum(fail), OGLStencilOperationConvertor::toGLenum(depthFail),
      OGLStencilOperationConvertor::toGLenum(depthPass));
}

void OGLStateContext::setPolygonMode(PolygonMode mode) {
#ifdef EMSCRIPTEN_PLATFORM
#else
  switch (mode) {
    case PolygonMode::LINE:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;

    case PolygonMode::NONE:
    case PolygonMode::FILL:
    default:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
#endif
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
