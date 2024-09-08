#ifndef SWAY_GAPI_GL_OGLSTATEENABLEABLE_HPP
#define SWAY_GAPI_GL_OGLSTATEENABLEABLE_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>
#include <sway/gapi/stateenableable.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

template <typename TConcreteData>
struct OGLStateEnableable : public StateEnableable<TConcreteData> {
  OGLStateEnableable(OGLStateHelper *helper)
      : helper_(helper) {}

  MTHD_OVERRIDE(auto capture() -> TConcreteData) {}

  MTHD_OVERRIDE(void apply(StateContext *state, const TConcreteData &data)) {}

protected:
  OGLStateHelper *helper_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTATEENABLEABLE_HPP
