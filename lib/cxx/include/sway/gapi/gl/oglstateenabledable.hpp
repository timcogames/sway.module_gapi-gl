#ifndef SWAY_GAPI_GL_OGLSTATEENABLEDABLE_HPP
#define SWAY_GAPI_GL_OGLSTATEENABLEDABLE_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLStateEnabledable {
  bool enabled = false;

  OGLStateEnabledable(u32_t cap)
      : capability_(cap) {}

protected:
  void onSaveCurrentState_() { enabled = (glIsEnabled(capability_) != 0); }

  void onUpdateState_() { (enabled ? glEnable : glDisable)(capability_); }

private:
  u32_t capability_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTATEENABLEDABLE_HPP
