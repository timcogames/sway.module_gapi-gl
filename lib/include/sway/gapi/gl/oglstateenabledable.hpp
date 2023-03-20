#ifndef SWAY_GAPI_GL_OGLSTATEENABLEDABLE_HPP
#define SWAY_GAPI_GL_OGLSTATEENABLEDABLE_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLStateEnabledable {
  bool enabled;

  [[nodiscard]] auto isEnabled(u32_t cap) const -> bool {
    (enabled ? glEnable : glDisable)(cap);
    return enabled;
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTATEENABLEDABLE_HPP
