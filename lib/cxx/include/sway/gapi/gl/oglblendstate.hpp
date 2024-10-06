#ifndef SWAY_GAPI_GL_OGLBLENDSTATE_HPP
#define SWAY_GAPI_GL_OGLBLENDSTATE_HPP

#include <sway/gapi/gl/oglblendequationconvertor.hpp>
#include <sway/gapi/gl/oglblendfunctionconvertor.hpp>
#include <sway/gapi/gl/oglstateenabledable.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

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

struct BlendStateData : public StateEnableableData {
  math::col4f_t color;
  BlendFactor factor;
  BlendMode mode;
};

struct OGLBlendState : public OGLStateEnableable<BlendStateData> {
  OGLBlendState(OGLStateHelper *helper)
      : OGLStateEnableable<BlendStateData>(helper) {}

  MTHD_OVERRIDE(auto capture() -> BlendStateData) {
    // glGetIntegerv(GL_BLEND_SRC_RGB, (GLint *)&factor.src.rgb);
    // glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint *)&factor.src.alpha);
    // glGetIntegerv(GL_BLEND_DST_RGB, (GLint *)&factor.dst.rgb);
    // glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint *)&factor.dst.alpha);
    // glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint *)&mode.eqn.rgb);
    // glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint *)&mode.eqn.alpha);

    return (struct BlendStateData){
        // .enabled = this->enabled,
        // .color = this->color,
        // .factor = this->factor,
        // .mode = this->mode
    };
  }

  //   color = math::col4f_t(0.0F, 0.0F, 0.0F, 0.0F);
  //   factor.src.rgb = OGLBlendFunctionConvertor::toGLenum(BlendFunction::ONE);
  //   factor.src.alpha = OGLBlendFunctionConvertor::toGLenum(BlendFunction::ONE);
  //   factor.dst.rgb = OGLBlendFunctionConvertor::toGLenum(BlendFunction::ZERO);
  //   factor.dst.alpha = OGLBlendFunctionConvertor::toGLenum(BlendFunction::ZERO);
  //   mode.eqn.rgb = OGLBlendEquationConvertor::toGLenum(BlendEquation::ADD);
  //   mode.eqn.alpha = OGLBlendEquationConvertor::toGLenum(BlendEquation::ADD);

  MTHD_OVERRIDE(void apply(StateContext *state, const BlendStateData &data)) {
    // if (!this->enabled) {
    //   return;
    // }

    // if (dirty.is(DirtyFlag::BLEND_COLOR)) {
    //   glBlendColor(color.getR(), color.getG(), color.getB(), color.getA());
    // }

    this->helper_->blendFuncSeparate(
        data.factor.src.rgb, data.factor.dst.rgb, data.factor.src.alpha, data.factor.dst.alpha);
    this->helper_->blendEquationSeparate(data.mode.eqn.rgb, data.mode.eqn.alpha);
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLBLENDSTATE_HPP
