#ifndef SWAY_GAPI_GL_OGLSTATEENABLEABLE_HPP
#define SWAY_GAPI_GL_OGLSTATEENABLEABLE_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>
#include <sway/gapi/stateenableable.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

template <typename CONCRETE_DATA>
struct OGLStateEnableable : public StateEnableable<CONCRETE_DATA> {
  OGLStateEnableable()
      : helper_(new OGLStateHelper()) {}

  OGLStateEnableable(OGLStateHelper *helper)
      : helper_(helper) {}

  MTHD_OVERRIDE(auto capture() -> CONCRETE_DATA) {}

  MTHD_OVERRIDE(void apply(StateContext *state, const CONCRETE_DATA &data)) {}

protected:
  OGLStateHelper *helper_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLSTATEENABLEABLE_HPP
