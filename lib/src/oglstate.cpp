#include <sway/gapi/gl/oglstate.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLState::createInstance() -> StateRef_t {
  auto instance = std::make_shared<OGLState>();
  return instance;
}

auto OGLState::getBlendFunction(BlendFunction fnc) -> u32_t {
  switch (fnc) {
    case BlendFunction::ZERO:
      return GL_ZERO;
    case BlendFunction::ONE:
      return GL_ONE;
    case BlendFunction::SRC_COLOR:
      return GL_SRC_COLOR;
    case BlendFunction::ONE_MINUS_SRC_COLOR:
      return GL_ONE_MINUS_SRC_COLOR;
    case BlendFunction::DST_COLOR:
      return GL_DST_COLOR;
    case BlendFunction::ONE_MINUS_DST_COLOR:
      return GL_ONE_MINUS_DST_COLOR;
    case BlendFunction::SRC_ALPHA:
      return GL_SRC_ALPHA;
    case BlendFunction::ONE_MINUS_SRC_ALPHA:
      return GL_ONE_MINUS_SRC_ALPHA;
    case BlendFunction::DST_ALPHA:
      return GL_DST_ALPHA;
    case BlendFunction::ONE_MINUS_DST_ALPHA:
      return GL_ONE_MINUS_DST_ALPHA;
    case BlendFunction::SRC_ALPHA_SATURATE:
      return GL_SRC_ALPHA_SATURATE;
    default:
      return 0;
      // throw std::runtime_error("Unknown function: " + std::to_string(fnc));
  }
}

auto OGLState::getBlendEquation(BlendEquation eqn) -> u32_t {
  switch (eqn) {
    case BlendEquation::ADD:
      return GL_FUNC_ADD;
    case BlendEquation::SUBTRACT:
      return GL_FUNC_SUBTRACT;
    case BlendEquation::REVERSE_SUBTRACT:
      return GL_FUNC_REVERSE_SUBTRACT;
    case BlendEquation::MIN:
      return GL_MIN;
    case BlendEquation::MAX:
      return GL_MAX;
    default:
      // throw std::runtime_error("Unknown equation: " + std::to_string(eqn));
      return 0;
  }
}

OGLState::OGLState() {}

void OGLState::enable(u32_t cap, bool state) { (state ? glEnable : glDisable)(cap); }

// gapi::BlendFunction::SRC_ALPHA
// gapi::BlendFunction::ONE_MINUS_SRC_ALPHA
void OGLState::setBlend() {
  blend_.initialize();
  blend_.enable = true;
  blend_.factor.src.rgb = OGLState::getBlendFunction(BlendFunction::ONE);
  blend_.factor.src.alpha = OGLState::getBlendFunction(BlendFunction::ONE);
  blend_.factor.dst.rgb = OGLState::getBlendFunction(BlendFunction::ZERO);
  blend_.factor.dst.alpha = OGLState::getBlendFunction(BlendFunction::ZERO);
  blend_.mode.eqn.rgb = OGLState::getBlendEquation(BlendEquation::ADD);
  blend_.mode.eqn.alpha = OGLState::getBlendEquation(BlendEquation::ADD);
  blend_.apply(helper_);

  // if (dirty_.flags(Dirty::BLEND_COLOR)) {
  //   glBlendColor(blend_.color.getR(), blend_.color.getG(), blend_.color.getB(), blend_.color.getA());
  // }
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
