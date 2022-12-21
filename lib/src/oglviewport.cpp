#include <sway/gapi/gl/oglviewport.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLViewport::createInstance() -> ViewportRef_t {
  auto instance = std::make_shared<OGLViewport>();
  return instance;
}

OGLViewport::OGLViewport()
//: mode_(ViewportMode_t::kEnabled)
{}

void OGLViewport::set(s32_t x, s32_t y, s32_t w, s32_t h) { glViewport(x, y, w, h); }

void OGLViewport::set(s32_t w, s32_t h) { set(0, 0, w, h); }

auto OGLViewport::get() const -> math::rect4i_t {
  s32_t viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  return {viewport[0], viewport[1], viewport[2], viewport[3]};
}

auto OGLViewport::aspect() const -> f32_t {
  math::rect4i_t const rect = get();
  return (f32_t)rect.getW() / (f32_t)rect.getH();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
