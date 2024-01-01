#ifndef SWAY_GAPI_GL_OGLSTENCILSTATE_HPP
#define SWAY_GAPI_GL_OGLSTENCILSTATE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl/oglstateenabledable.hpp>
#include <sway/gapi/gl/oglstencilfunctionconvertor.hpp>
#include <sway/gapi/gl/oglstenciloperationconvertor.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLStencilState : public OGLStateEnabledable {
  u32_t stencilFunc;
  u32_t stencilFail;
  u32_t depthFail;
  u32_t depthPass;

  OGLStencilState()
      : OGLStateEnabledable(GL_STENCIL_TEST) {}

  void capture() { this->onSaveCurrentState_(); }

  void apply([[maybe_unused]] OGLStateHelper helper) {
    this->onUpdateState_();
    if (!this->enabled) {
      return;
    }

    glStencilOp(OGLStencilOperationConvertor::toGLenum(stencilFail), OGLStencilOperationConvertor::toGLenum(depthFail),
        OGLStencilOperationConvertor::toGLenum(depthPass));
    glStencilFunc(OGLStencilFunctionConvertor::toGLenum(stencilFunc), 1, 0xFF);
    glStencilMask(0xFF);
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTENCILSTATE_HPP
