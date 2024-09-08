#ifndef SWAY_GAPI_GL_OGLRASTERIZERSTATE_HPP
#define SWAY_GAPI_GL_OGLRASTERIZERSTATE_HPP

#include <sway/gapi/gl/oglcullfaceconvertor.hpp>
#include <sway/gapi/gl/oglfrontfaceconvertor.hpp>
#include <sway/gapi/gl/oglstateenabledable.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLRasterizerState : public OGLStateEnableable<RasterizerDescriptor> {
  OGLRasterizerState(OGLStateHelper *helper)
      : OGLStateEnableable<RasterizerDescriptor>(helper) {}

  MTHD_OVERRIDE(auto capture() -> RasterizerDescriptor) {
    return (struct RasterizerDescriptor){
        // .mode = OGLCullFaceConvertor::current(),
        // .ccw = OGLFrontFaceConvertor::current()
    };
  }

  MTHD_OVERRIDE(void apply(StateContext *state, const RasterizerDescriptor &desc)) {
    // if (!data.enabled) {
    //   return;
    // }

    glCullFace(OGLCullFaceConvertor::toGLenum(desc.mode));
    glFrontFace(OGLFrontFaceConvertor::toGLenum(desc.ccw ? FrontFace::COUNTER_CLOCK_WISE : FrontFace::CLOCK_WISE));
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLRASTERIZERSTATE_HPP
