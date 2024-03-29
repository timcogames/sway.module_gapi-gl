#include <sway/gapi/gl/oglclearflagconvertor.hpp>
#include <sway/gapi/gl/oglviewport.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLViewport::createInstance() -> ViewportRef_t {
  auto instance = std::make_shared<OGLViewport>();
  return instance;
}

OGLViewport::OGLViewport()
    : mode_(ViewportMode::ENABLED)
    , clearColor_({0.0F, 0.0F, 0.0F, 1.0F}) {}

void OGLViewport::set(s32_t posX, s32_t posY, s32_t width, s32_t height) { glViewport(posX, posY, width, height); }

void OGLViewport::set(s32_t width, s32_t height) { set(0, 0, width, height); }

auto OGLViewport::get() const -> math::rect4i_t {
  std::array<s32_t, 4> viewport;
  glGetIntegerv(GL_VIEWPORT, viewport.data());
  return {viewport[0], viewport[1], viewport[2], viewport[3]};
}

auto OGLViewport::aspect() const -> f32_t {
  math::rect4i_t const rect = get();
  return (f32_t)rect.getW() / (f32_t)rect.getH();
}

void OGLViewport::clear() {
  glColorMask(1U, 1U, 1U, 1U);
  glDepthMask(1U);
  glStencilMask(0);
  glClearColor(clearColor_.getR(), clearColor_.getG(), clearColor_.getB(), clearColor_.getA());
  glClear(OGLClearFlagConvertor::toGLbitfield(ClearFlag::COLOR | ClearFlag::DEPTH | ClearFlag::STENCIL));
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
