#include <sway/core.hpp>
#include <sway/gapi/gl.hpp>

#undef None
#undef Bool

#include <gtest/gtest.h>

using namespace sway;

TEST(VertexSemantics, Stringize) {
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kPosition), "attr_position");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kColor), "attr_color");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kTexCoord_0), "attr_texcoord_0");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kTexCoord_1), "attr_texcoord_1");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kTexCoord_2), "attr_texcoord_2");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kTexCoord_3), "attr_texcoord_3");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kTexCoord_4), "attr_texcoord_4");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kTexCoord_5), "attr_texcoord_5");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kTexCoord_6), "attr_texcoord_6");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kTexCoord_7), "attr_texcoord_7");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kNormal), "attr_normal");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kTangent), "attr_tangent");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kBinormal), "attr_binormal");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kBlendWeights), "attr_blend_weights");
  ASSERT_EQ(stringize(gapi::VertexSemantic_t::kBlendIndices), "attr_blend_indices");
}
