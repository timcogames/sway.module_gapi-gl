#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

#undef None
#undef Bool

#include <gtest/gtest.h>

using namespace sway;

TEST(VertexSemantics, Stringize) {
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::Position), "attr_position");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::Color), "attr_color");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::TexCoord_0), "attr_texcoord_0");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::TexCoord_1), "attr_texcoord_1");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::TexCoord_2), "attr_texcoord_2");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::TexCoord_3), "attr_texcoord_3");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::TexCoord_4), "attr_texcoord_4");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::TexCoord_5), "attr_texcoord_5");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::TexCoord_6), "attr_texcoord_6");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::TexCoord_7), "attr_texcoord_7");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::Normal), "attr_normal");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::Tangent), "attr_tangent");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::Binormal), "attr_binormal");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::BlendWeights), "attr_blend_weights");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::BlendIndices), "attr_blend_indices");
}
