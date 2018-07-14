#include <sway/gapi/vertexlayout.h>
#include <sway/gapi/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

template<typename TYPE>
inline void VertexLayout::addAttribute(VertexSemantic_t semantic) {
	std::string name = stringize(semantic);
	s32_t location = Extensions::glGetAttribLocationARB(_program->getId(), name.c_str());
	
	if (location >= 0 && location <= _maxVertexAttributes) {
		VertexAttribute attrib;
		attrib.location = location;
		attrib.semantic = semantic;
		attrib.format = core::detail::TypeToEnum<typename TYPE::rawtype_t>::value;
		attrib.numComponents = TYPE::size();
		attrib.stride = sizeof(typename TYPE::rawtype_t) * TYPE::size();
		attrib.offset = BUFFER_OFFSET(_attributeOffset);
		attrib.normalized = false;
		attrib.enabled = true;

		_attributes.insert(std::make_pair(name, attrib));
		_attributeOffset += attrib.stride;
	}
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
