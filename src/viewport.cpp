#include <sway/gapi/viewport.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

Viewport::Viewport() {
	// Empty
}

Viewport::~Viewport() {
	// Empty
}

void Viewport::set(s32_t x, s32_t y, s32_t w, s32_t h) {
	glViewport(x, y, w, h);
}

void Viewport::set(s32_t w, s32_t h) {
	set(0, 0, w, h);
}

math::TRect<s32_t> Viewport::get() const {
	s32_t viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	return math::TRect<s32_t>(viewport[0], viewport[1], viewport[2], viewport[3]);
}

f32_t Viewport::aspect() const {
	math::TRect<s32_t> rect = get();
	return (f32_t) rect.getW() / (f32_t) rect.getH();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
