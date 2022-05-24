#include <sway/gapi/gl/viewport.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

ViewportRef_t Viewport::createInstance() {
  auto instance = std::make_shared<Viewport>();
  return instance;
}

Viewport::Viewport()
//: mode_(ViewportMode_t::kEnabled)
{}

void Viewport::set(s32_t x, s32_t y, s32_t w, s32_t h) { glViewport(x, y, w, h); }

void Viewport::set(s32_t w, s32_t h) { set(0, 0, w, h); }

math::rect4i_t Viewport::get() const {
  s32_t viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  return math::rect4i_t(viewport[0], viewport[1], viewport[2], viewport[3]);
}

f32_t Viewport::aspect() const {
  math::rect4i_t rect = get();
  return (f32_t)rect.getW() / (f32_t)rect.getH();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
