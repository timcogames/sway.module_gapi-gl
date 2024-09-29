#include "./unit/mockoglbufferidgenhelper.hpp"

#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

#undef None
#undef Bool

#include <gtest/gtest.h>

using namespace sway;

TEST(BufferIdGenerator, get_next_uid) {
  testing::NiceMock<MockOGLBufferIdgenHelper> mock;
  EXPECT_CALL(mock, generateBuffers(testing::_, testing::_, testing::_)).Times(2);

  gapi::OGLBufferIdGenerator idgen(mock);
  for (auto i = 0; i < 12; ++i) {
    idgen.getNextUid();
  }

  ASSERT_EQ(idgen.getNextUid(), 13);
}
