#ifndef SWAY_GAPI_GL_OGLDEPTHSTATE_HPP
#define SWAY_GAPI_GL_OGLDEPTHSTATE_HPP

#include <sway/gapi/gl/oglstateenabledable.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

#include <bitset>
#include <limits>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

struct DepthStateData : public StateEnableableData {
  CompareFn::Enum func;
  bool mask;
  // math::vec2d_t range;
  f64_t near;
  f64_t far;
};

struct OGLDepthState : public OGLStateEnableable<DepthStateData> {
  OGLDepthState(OGLStateHelper *helper)
      : OGLStateEnableable<DepthStateData>(helper) {}

  MTHD_OVERRIDE(auto capture() -> DepthStateData) {

    // GLint *funcPtr = nullptr;
    // glGetIntegerv(GL_DEPTH_FUNC, funcPtr);

    // GLboolean *maskPtr = nullptr;
    // glGetBooleanv(GL_DEPTH_WRITEMASK, maskPtr);

    // GLdouble depthRange[2];
    // glGetDoublev(GL_DEPTH_RANGE, depthRange);

    return (struct DepthStateData){
        // .enabled = this->enabled,
        // .func = OGLBlendFunctionConvertor::fromGLenum((u32_t)&funcPtr),
        // .mask = (bool)&maskPtr,
        // .near = depthRange[0],
        // .far = depthRange[1]
    };
  }

  MTHD_OVERRIDE(void apply(StateContext *state, const DepthStateData &data)) {
    // if (!this->enabled) {
    //   return;
    // }

    // glClearDepth(depth_clear_);

    state->setDepthFn(data.func);
    state->setDepthMask(data.mask);
    glDepthRange(data.near, data.far);
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLDEPTHSTATE_HPP
