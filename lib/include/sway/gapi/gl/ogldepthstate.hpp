#ifndef SWAY_GAPI_GL_OGLDEPTHSTATE_HPP
#define SWAY_GAPI_GL_OGLDEPTHSTATE_HPP

#include <sway/gapi/gl/oglstateenabledable.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

#include <bitset>
#include <limits>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLDepthState : public OGLStateEnabledable {
  u32_t func;
  bool mask;
  math::vec3d_t range;
  f64_t near;
  f64_t far;

  OGLDepthState() {
    enabled = true;
    func = GL_NEVER;
    mask = false;
  }

  void capture() {
    enabled = (glIsEnabled(GL_DEPTH_TEST) != 0U);
    glGetIntegerv(GL_DEPTH_FUNC, (s32_t *)&func);
  }

  void apply([[maybe_unused]] OGLStateHelper helper /*, [[maybe_unused]] DirtyState dirty*/) {
    if (!isEnabled(GL_DEPTH_TEST)) {
      return;
    }

    // glClearDepth(depth_clear_);

    glDepthFunc(func);

    glDepthMask(mask);
    glDepthRange(range.getX(), range.getY());
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLDEPTHSTATE_HPP
