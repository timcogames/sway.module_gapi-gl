#include <sway/gapi/gl/oglclearflagconvertor.hpp>
#include <sway/gapi/gl/oglviewport.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLViewport::createInstance() -> ViewportPtr_t {
  auto instance = new OGLViewport();
  return instance;
}

OGLViewport::OGLViewport()
    : mode_(ViewportMode::Enum::ENABLED)
    , clearColor_({0.0F, 0.0F, 0.0F, 1.0F}) {}

void OGLViewport::set(i32_t posX, i32_t posY, i32_t width, i32_t height) { glViewport(posX, posY, width, height); }

void OGLViewport::set(i32_t width, i32_t height) { set(0, 0, width, height); }

auto OGLViewport::get() const -> math::rect4i_t {
  std::array<i32_t, 4> viewport;
  glGetIntegerv(GL_VIEWPORT, viewport.data());
  return {viewport[0], viewport[1], viewport[2], viewport[3]};
}

auto OGLViewport::aspect() const -> f32_t {
  math::rect4i_t const rect = get();
  return (f32_t)rect.getW() / (f32_t)rect.getH();
}

void OGLViewport::setClearColor(const math::col4f_t &col) {
  clearColor_ = math::col4f_t(col.getR() / 255.0F, col.getG() / 255.0F, col.getB() / 255.0F, col.getA() / 255.0F);
}

void OGLViewport::clear(ClearFlag flags) {
  glClearColor(clearColor_.getR(), clearColor_.getG(), clearColor_.getB(), clearColor_.getA());
  glClear(OGLClearFlagConvertor::toGLbitfield(flags));
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
