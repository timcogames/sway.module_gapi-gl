#ifndef SWAY_GAPI_GL_OGLCULLSTATE_HPP
#define SWAY_GAPI_GL_OGLCULLSTATE_HPP

#include <sway/gapi/gl/oglcullfaceconvertor.hpp>
#include <sway/gapi/gl/oglfrontfaceconvertor.hpp>
#include <sway/gapi/gl/oglstateenabledable.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLCullState : public OGLStateEnabledable {
  u32_t mode;
  u32_t front;

  OGLCullState()
      : OGLStateEnabledable(GL_CULL_FACE) {
    mode = OGLCullFaceConvertor::toGLenum(CullFace::BACK);
    front = OGLFrontFaceConvertor::toGLenum(FrontFace::COUNTER_CLOCK_WISE);
  }

  void capture() {
    this->onSaveCurrentState_();

    glGetIntegerv(GL_CULL_FACE_MODE, (s32_t *)&mode);
    glGetIntegerv(GL_FRONT_FACE, (s32_t *)&front);
  }

  void apply([[maybe_unused]] OGLStateHelper helper /*, [[maybe_unused]] DirtyState dirty*/) {
    this->onUpdateState_();
    if (!this->enabled) {
      return;
    }

    glCullFace(mode);
    glFrontFace(front);
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLCULLSTATE_HPP
