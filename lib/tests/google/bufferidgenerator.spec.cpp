#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

#undef None
#undef Bool

#include <gtest/gtest.h>

using namespace sway;

TEST(BufferIdGenerator, newGuid) {
  auto idGenerator = gapi::BufferIdGenerator::createInstance();
  for (auto i = 0; i < 12; ++i) {
    idGenerator->newGuid();
  }

  ASSERT_EQ(idGenerator->newGuid(), 13);
}
