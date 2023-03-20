#ifndef SWAY_GAPI_GL_OGLSTATE_HPP
#define SWAY_GAPI_GL_OGLSTATE_HPP

#include <sway/gapi/gl/oglblendstate.hpp>
#include <sway/gapi/gl/oglcullstate.hpp>
#include <sway/gapi/gl/ogldepthstate.hpp>
#include <sway/gapi/gl/oglstateenabledable.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

#include <bitset>
#include <limits>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

enum class DirtyFlag { BLEND_COLOR };

struct DirtyState {
  std::bitset<std::numeric_limits<u8_t>::max()> flags;

  // auto is(DirtyFlag flag) -> bool {
  //   if (!flags[flag]) {
  //     return false;
  //   }

  //   flags[flag] = false;
  //   return true;
  // }
};

class OGLState : public State {
public:
  static auto createInstance() -> StateRef_t;

  OGLState();

  virtual ~OGLState() = default;

  MTHD_OVERRIDE(void apply());

private:
  OGLStateHelper helper_;
  DirtyState dirty_;

  OGLBlendState blend_;
  OGLDepthState depth_;
  OGLCullState cull_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTATE_HPP
