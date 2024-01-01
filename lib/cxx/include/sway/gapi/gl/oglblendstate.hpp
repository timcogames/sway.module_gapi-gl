#ifndef SWAY_GAPI_GL_OGLBLENDSTATE_HPP
#define SWAY_GAPI_GL_OGLBLENDSTATE_HPP

#include <sway/gapi/gl/oglblendequationconvertor.hpp>
#include <sway/gapi/gl/oglblendfunctionconvertor.hpp>
#include <sway/gapi/gl/oglstateenabledable.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglstatehelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

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

struct OGLBlendState : public OGLStateEnabledable {
  math::col4f_t color;
  BlendFactor factor;
  BlendMode mode;

  OGLBlendState()
      : OGLStateEnabledable(GL_BLEND) {
    color = math::col4f_t(0.0F, 0.0F, 0.0F, 0.0F);
    factor.src.rgb = OGLBlendFunctionConvertor::toGLenum(BlendFunction::ONE);
    factor.src.alpha = OGLBlendFunctionConvertor::toGLenum(BlendFunction::ONE);
    factor.dst.rgb = OGLBlendFunctionConvertor::toGLenum(BlendFunction::ZERO);
    factor.dst.alpha = OGLBlendFunctionConvertor::toGLenum(BlendFunction::ZERO);
    mode.eqn.rgb = OGLBlendEquationConvertor::toGLenum(BlendEquation::ADD);
    mode.eqn.alpha = OGLBlendEquationConvertor::toGLenum(BlendEquation::ADD);
  }

  void capture() {
    this->onSaveCurrentState_();

    glGetIntegerv(GL_BLEND_SRC_RGB, (GLint *)&factor.src.rgb);
    glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint *)&factor.src.alpha);
    glGetIntegerv(GL_BLEND_DST_RGB, (GLint *)&factor.dst.rgb);
    glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint *)&factor.dst.alpha);
    glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint *)&mode.eqn.rgb);
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint *)&mode.eqn.alpha);
  }

  void apply(OGLStateHelper helper /*, [[maybe_unused]] DirtyState dirty*/) {
    this->onUpdateState_();
    if (!this->enabled) {
      return;
    }

    // if (dirty.is(DirtyFlag::BLEND_COLOR)) {
    //   glBlendColor(color.getR(), color.getG(), color.getB(), color.getA());
    // }

    helper.blendFuncSeparate(factor.src.rgb, factor.dst.rgb, factor.src.alpha, factor.dst.alpha);
    helper.blendEquationSeparate(mode.eqn.rgb, mode.eqn.alpha);
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLBLENDSTATE_HPP
