#include "./unit/mockoglgenericshaderhelper.hpp"

#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

#undef None
#undef Bool

#include <gtest/gtest.h>

using namespace sway;

class GenericShaderTest : public testing::Test {
public:
  void setup() { EXPECT_CALL(mock_, createShader(testing::_)).WillRepeatedly(testing::Return(objectId_)); }

protected:
  testing::NiceMock<MockOGLGenericShaderHelper> mock_;
  const u32_t objectId_ = 123;
};

TEST_F(GenericShaderTest, Ctor) {
  setup();

  gapi::OGLGenericShader shader(mock_, gapi::ShaderType::VERT);
  EXPECT_EQ(shader.getUid().value(), objectId_);
}
