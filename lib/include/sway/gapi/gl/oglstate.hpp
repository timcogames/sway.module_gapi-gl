#ifndef SWAY_GAPI_GL_OGLSTATE_HPP
#define SWAY_GAPI_GL_OGLSTATE_HPP

#include <sway/gapi/blendequations.hpp>
#include <sway/gapi/blendfunctions.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

#include <bitset>
#include <limits>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

enum class Dirty { BLEND_COLOR };

struct DirtyState {
  std::bitset<std::numeric_limits<u8_t>::max()> flags;
};

struct BlendAttrib {
  u32_t rgb;
  u32_t alpha;
};

struct BlendFactor {
  BlendAttrib src;
  BlendAttrib dst;
};

struct BlendMode {
  BlendAttrib eqn;
};

struct BlendState {
  bool enable;
  BlendFactor factor;
  BlendMode mode;

  void initialize() {
    enable = glIsEnabled(GL_BLEND);
    glGetIntegerv(GL_BLEND_SRC_RGB, (GLint *)&factor.src.rgb);
    glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint *)&factor.src.alpha);
    glGetIntegerv(GL_BLEND_DST_RGB, (GLint *)&factor.dst.rgb);
    glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint *)&factor.dst.alpha);
    glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint *)&mode.eqn.rgb);
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint *)&mode.eqn.alpha);
  }

  void apply(OGLStateHelper helper) {
    if (!enable) {
      glDisable(GL_BLEND);
      return;
    }

    glEnable(GL_BLEND);
    helper.blendFuncSeparate(factor.src.rgb, factor.dst.rgb, factor.src.alpha, factor.dst.alpha);
    helper.blendEquationSeparate(mode.eqn.rgb, mode.eqn.alpha);
  }
};

class OGLState : public State {
public:
  static auto createInstance() -> StateRef_t;

  static auto getBlendFunction(BlendFunction fnc) -> u32_t;

  static auto getBlendEquation(BlendEquation eqn) -> u32_t;

  OGLState();

  virtual ~OGLState() = default;

  void enable(u32_t cap, bool state);

  MTHD_OVERRIDE(void setBlend());

private:
  OGLStateHelper helper_;
  DirtyState dirty_;
  BlendState blend_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSTATE_HPP
