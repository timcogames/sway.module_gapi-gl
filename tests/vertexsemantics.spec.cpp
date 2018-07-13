#include <boost/test/unit_test.hpp>
#include <sway/core.h>
#include <sway/gapi.h>

using namespace sway;

BOOST_AUTO_TEST_SUITE(VertexSemantics_TestSuite)

BOOST_AUTO_TEST_CASE(VertexSemantics_TestCase_Stringize) {
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kPosition), "attr_position");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kColor), "attr_color");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kTexCoord_0), "attr_texcoord_0");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kTexCoord_1), "attr_texcoord_1");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kTexCoord_2), "attr_texcoord_2");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kTexCoord_3), "attr_texcoord_3");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kTexCoord_4), "attr_texcoord_4");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kTexCoord_5), "attr_texcoord_5");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kTexCoord_6), "attr_texcoord_6");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kTexCoord_7), "attr_texcoord_7");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kNormal), "attr_normal");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kTangent), "attr_tangent");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kBinormal), "attr_binormal");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kBlendWeights), "attr_blend_weights");
	BOOST_CHECK_EQUAL(stringize(gapi::VertexSemantic_t::kBlendIndices), "attr_blend_indices");
}

BOOST_AUTO_TEST_SUITE_END()
