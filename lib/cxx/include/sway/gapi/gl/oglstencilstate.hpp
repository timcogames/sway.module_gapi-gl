#ifndef SWAY_GAPI_GL_OGLSTENCILSTATE_HPP
#define SWAY_GAPI_GL_OGLSTENCILSTATE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl/oglcomparefunctionconvertor.hpp>
#include <sway/gapi/gl/oglstateenabledable.hpp>
#include <sway/gapi/gl/oglstenciloperationconvertor.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct StencilStateData : public StateEnableableData {
  CompareFn func;
  u32_t ref;
  u32_t mask;
  StencilOp fail;
  StencilOp depthFail;
  StencilOp depthPass;
};

struct OGLStencilState : public OGLStateEnableable<StencilStateData> {
  OGLStencilState(OGLStateHelper *helper)
      : OGLStateEnableable<StencilStateData>(helper) {}

  // clang-format off
  MTHD_OVERRIDE(auto capture() -> StencilStateData) {  // clang-format on
    // GLint *funcPtr = nullptr;
    // glGetIntegerv(GL_STENCIL_FUNC, funcPtr);

    // GLint *refPtr = nullptr;
    // glGetIntegerv(GL_STENCIL_REF, refPtr);

    // GLint *maskPtr = nullptr;
    // glGetIntegerv(GL_STENCIL_VALUE_MASK, maskPtr);

    // GLint *failPtr = nullptr;
    // glGetIntegerv(GL_STENCIL_FAIL, failPtr);

    // GLint *depthFailPtr = nullptr;
    // glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, depthFailPtr);

    // GLint *depthPassPtr = nullptr;
    // glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, depthPassPtr);

    return (struct StencilStateData){
        // .enabled = this->enabled,
        // .func = OGLCompareFunctionConvertor::fromGLenum((GLenum)&funcPtr),
        // .ref = (u32_t)&refPtr,
        // .mask = (u32_t)&maskPtr,
        // .fail = OGLStencilOperationConvertor::fromGLenum((GLenum)&failPtr),
        // .depthFail = OGLStencilOperationConvertor::fromGLenum((GLenum)&depthFailPtr),
        // .depthPass = OGLStencilOperationConvertor::fromGLenum((GLenum)&depthPassPtr)
    };
  }

  MTHD_OVERRIDE(void apply(StateContext *state, const StencilStateData &data)) {
    // if (!this->enabled) {
    //   return;
    // }

    state->setStencilFn(data.func, data.ref, data.mask);
    state->setStencilOp(data.fail, data.depthFail, data.depthPass);
    state->setStencilMask(data.mask);
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTENCILSTATE_HPP
