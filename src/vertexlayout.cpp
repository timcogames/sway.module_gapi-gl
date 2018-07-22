#include <sway/gapi/gl/vertexlayout.h>
#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

VertexLayout::VertexLayout(IShaderProgramBase * shader) : IVertexLayoutBase(shader)
	, _attributeOffset(0)
	, _shaderProgram(shader) {
	/* Получаем максимальный номер для положения вершинного атрибута. */
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxVertexAttributes);
}

VertexLayout::~VertexLayout() {
	_attributes.clear();
}

void VertexLayout::addAttribute(VertexAttributeDescriptor attributeDesc) {
	std::string alias = stringize(attributeDesc.semantic);
	s32_t location = Extensions::glGetAttribLocationARB(_shaderProgram->getObjectId(), alias.c_str());
	
	attributeDesc.location = location;
	attributeDesc.offset = BUFFER_OFFSET(_attributeOffset);

	if (location >= 0 && location <= _maxVertexAttributes) {
		_attributes.insert(std::make_pair(alias, attributeDesc));
		_attributeOffset += attributeDesc.stride;
	}
}

void VertexLayout::enable() {
	BOOST_FOREACH(VertexAttributeDescriptor & attrib, _attributes | boost::adaptors::map_values) {
		if (attrib.enabled) {
			Extensions::glEnableVertexAttribArrayARB(attrib.location);
			Extensions::glVertexAttribPointerARB(attrib.location, attrib.numComponents, TypeUtils::toGL(attrib.format), attrib.normalized, attrib.stride, attrib.offset);
		}
	}
}

void VertexLayout::disable() {
	BOOST_FOREACH(VertexAttributeDescriptor & attrib, _attributes | boost::adaptors::map_values) {
		if (attrib.enabled)
			Extensions::glDisableVertexAttribArrayARB(attrib.location);
	}
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)