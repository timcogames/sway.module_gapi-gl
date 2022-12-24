#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

#undef None
#undef Bool

#include <gtest/gtest.h>

using namespace sway;

TEST(VertexSemantics, Stringize) {
  ASSERT_EQ(stringize(gapi::VertexSemantic::POS), "attrib_pos");
  ASSERT_EQ(stringize(gapi::VertexSemantic::COL), "attrib_col");
  ASSERT_EQ(stringize(gapi::VertexSemantic::TEXCOORD_0), "attrib_texcoord_0");
  ASSERT_EQ(stringize(gapi::VertexSemantic::TEXCOORD_1), "attrib_texcoord_1");
  ASSERT_EQ(stringize(gapi::VertexSemantic::TEXCOORD_2), "attrib_texcoord_2");
  ASSERT_EQ(stringize(gapi::VertexSemantic::TEXCOORD_3), "attrib_texcoord_3");
  ASSERT_EQ(stringize(gapi::VertexSemantic::TEXCOORD_4), "attrib_texcoord_4");
  ASSERT_EQ(stringize(gapi::VertexSemantic::TEXCOORD_5), "attrib_texcoord_5");
  ASSERT_EQ(stringize(gapi::VertexSemantic::TEXCOORD_6), "attrib_texcoord_6");
  ASSERT_EQ(stringize(gapi::VertexSemantic::TEXCOORD_7), "attrib_texcoord_7");
  ASSERT_EQ(stringize(gapi::VertexSemantic::NORMAL), "attrib_normal");
  ASSERT_EQ(stringize(gapi::VertexSemantic::TANGENT), "attrib_tangent");
  ASSERT_EQ(stringize(gapi::VertexSemantic::BINORMAL), "attrib_binormal");
  ASSERT_EQ(stringize(gapi::VertexSemantic::BLEND_WEIGHTS), "attrib_blend_weights");
  ASSERT_EQ(stringize(gapi::VertexSemantic::BLEND_INDICES), "attrib_blend_indices");
}
