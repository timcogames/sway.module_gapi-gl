#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

#undef None
#undef Bool

#include <gtest/gtest.h>

using namespace sway;

TEST(Viewport, clear_flag_conv) {
  ASSERT_TRUE(gapi::OGLClearFlagConvertor::toGLbitfield(
                  gapi::ClearFlag::COLOR | gapi::ClearFlag::DEPTH | gapi::ClearFlag::STENCIL) > 0);
}
