#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

#undef None
#undef Bool

#include <gtest/gtest.h>

using namespace sway;

TEST(ShaderPreprocessor, addDefine) {
  std::ostringstream out;
  auto preprocessor = gapi::OGLShaderPreprocessor::createInstance(core::Version(120, DONT_CARE, DONT_CARE, "core"));

  preprocessor->addDefine("ITEM1", "1");
  preprocessor->addDefine("ITEM2", "2");
  preprocessor->addDefine("ITEM3", "3");
  preprocessor->evaluate(out);

  std::string expected("#version 120 core\n"
                       "#define ITEM1 1\n"
                       "#define ITEM2 2\n"
                       "#define ITEM3 3\n");

  ASSERT_EQ(out.str(), expected);
}
