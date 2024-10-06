#include <sway/gapi/gl/oglblendfunctionconvertor.hpp>
#include <sway/gapi/gl/oglcomparefunctionconvertor.hpp>
#include <sway/gapi/gl/oglstatecapabilityconvertor.hpp>
#include <sway/gapi/gl/oglstatecontext.hpp>
#include <sway/gapi/gl/oglstenciloperationconvertor.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLStateContext::createInstance() -> StateContextPtr_t {
  auto *instance = new OGLStateContext();
  return instance;
}

OGLStateContext::OGLStateContext() {}

void OGLStateContext::setCapabilityEnable(StateCapability::Enum cap, bool enable) {
  (enable ? glEnable : glDisable)(OGLStateCapabilityConvertor::toGLenum(cap));
}

void OGLStateContext::setAlphaEnable(bool enable) { setCapabilityEnable(StateCapability::Enum::ALPHA_TEST, enable); }

void OGLStateContext::setAlphaFunc(CompareFn::Enum func, f32_t ref) {
  // glAlphaFunc(OGLCompareFunctionConvertor::toGLenum(func), ref);
  std::cout << "[setAlphaFunc]: Deprecated" << std::endl;
}

void OGLStateContext::setBlendEnable(bool enable) { setCapabilityEnable(StateCapability::Enum::BLEND, enable); }

void OGLStateContext::setBlendFn(BlendFn::Enum src, BlendFn::Enum dst) {
  glBlendFunc(OGLBlendFunctionConvertor::toGLenum(src), OGLBlendFunctionConvertor::toGLenum(dst));
}

void OGLStateContext::setDepthEnable(bool enable) { setCapabilityEnable(StateCapability::Enum::DEPTH_TEST, enable); }

void OGLStateContext::setClearDepth(f64_t depth) { glClearDepth(depth); }

void OGLStateContext::setDepthFn(CompareFn::Enum func) { glDepthFunc(OGLCompareFunctionConvertor::toGLenum(func)); }

void OGLStateContext::setDepthMask(bool flag) { glDepthMask(flag ? GL_TRUE : GL_FALSE); }

void OGLStateContext::setColorMask(bool red, bool green, bool blue, bool alpha) {
  glColorMask(red, green, blue, alpha);
}

void OGLStateContext::setStencilEnable(bool enable) {
  setCapabilityEnable(StateCapability::Enum::STENCIL_TEST, enable);
}

void OGLStateContext::setClearStencil(i32_t idx) { glClearStencil(idx); }

void OGLStateContext::setStencilMask(u32_t mask) { glStencilMask(mask); }

void OGLStateContext::setStencilFn(CompareFn::Enum func, i32_t ref, u32_t mask) {
  glStencilFunc(OGLCompareFunctionConvertor::toGLenum(func), ref, mask);
}

void OGLStateContext::setStencilOp(StencilOp::Enum fail, StencilOp::Enum depthFail, StencilOp::Enum depthPass) {
  glStencilOp(OGLStencilOperationConvertor::toGLenum(fail), OGLStencilOperationConvertor::toGLenum(depthFail),
      OGLStencilOperationConvertor::toGLenum(depthPass));
}

void OGLStateContext::setPolygonMode(PolygonMode::Enum mode) {
#ifdef EMSCRIPTEN_PLATFORM
#else
  switch (mode) {
    case PolygonMode::Enum::LINE:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;

    case PolygonMode::Enum::NONE:
    case PolygonMode::Enum::FILL:
    default:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
#endif
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
