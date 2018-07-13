#include <sway/gapi/vertexsemantics.h>

template<typename Type = char, typename Traits = std::char_traits<Type>>
inline std::basic_ostream<Type, Traits> & operator<<(std::basic_ostream<Type, Traits> & stream, sway::gapi::VertexSemantic_t value) {
	switch (value) {
		case sway::gapi::VertexSemantic_t::kPosition: return stream << "attr_position";
		case sway::gapi::VertexSemantic_t::kColor: return stream << "attr_color";
		case sway::gapi::VertexSemantic_t::kTexCoord_0: return stream << "attr_texcoord_0";
		case sway::gapi::VertexSemantic_t::kTexCoord_1: return stream << "attr_texcoord_1";
		case sway::gapi::VertexSemantic_t::kTexCoord_2: return stream << "attr_texcoord_2";
		case sway::gapi::VertexSemantic_t::kTexCoord_3: return stream << "attr_texcoord_3";
		case sway::gapi::VertexSemantic_t::kTexCoord_4: return stream << "attr_texcoord_4";
		case sway::gapi::VertexSemantic_t::kTexCoord_5: return stream << "attr_texcoord_5";
		case sway::gapi::VertexSemantic_t::kTexCoord_6: return stream << "attr_texcoord_6";
		case sway::gapi::VertexSemantic_t::kTexCoord_7: return stream << "attr_texcoord_7";
		case sway::gapi::VertexSemantic_t::kNormal: return stream << "attr_normal";
		case sway::gapi::VertexSemantic_t::kTangent: return stream << "attr_tangent";
		case sway::gapi::VertexSemantic_t::kBinormal: return stream << "attr_binormal";
		case sway::gapi::VertexSemantic_t::kBlendWeights: return stream << "attr_blend_weights";
		case sway::gapi::VertexSemantic_t::kBlendIndices: return stream << "attr_blend_indices";
		default:
			return stream << "unknown";
	}
}

template<typename Type = char, typename Traits = std::char_traits<Type>, typename Alloc = std::allocator<Type>>
inline std::basic_string<Type, Traits, Alloc> stringize(sway::gapi::VertexSemantic_t value) {
	switch (value) {
		case sway::gapi::VertexSemantic_t::kPosition: return "attr_position";
		case sway::gapi::VertexSemantic_t::kColor: return "attr_color";
		case sway::gapi::VertexSemantic_t::kTexCoord_0: return "attr_texcoord_0";
		case sway::gapi::VertexSemantic_t::kTexCoord_1: return "attr_texcoord_1";
		case sway::gapi::VertexSemantic_t::kTexCoord_2: return "attr_texcoord_2";
		case sway::gapi::VertexSemantic_t::kTexCoord_3: return "attr_texcoord_3";
		case sway::gapi::VertexSemantic_t::kTexCoord_4: return "attr_texcoord_4";
		case sway::gapi::VertexSemantic_t::kTexCoord_5: return "attr_texcoord_5";
		case sway::gapi::VertexSemantic_t::kTexCoord_6: return "attr_texcoord_6";
		case sway::gapi::VertexSemantic_t::kTexCoord_7: return "attr_texcoord_7";
		case sway::gapi::VertexSemantic_t::kNormal: return "attr_normal";
		case sway::gapi::VertexSemantic_t::kTangent: return "attr_tangent";
		case sway::gapi::VertexSemantic_t::kBinormal: return "attr_binormal";
		case sway::gapi::VertexSemantic_t::kBlendWeights: return "attr_blend_weights";
		case sway::gapi::VertexSemantic_t::kBlendIndices: return "attr_blend_indices";
		default:
			return "unknown";
	}
}
