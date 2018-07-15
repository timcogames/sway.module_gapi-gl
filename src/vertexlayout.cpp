#include <sway/gapi/gl/vertexlayout.h>
#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

VertexLayout::VertexLayout(ShaderProgram * program)
	: _attributeOffset(0)
	, _program(program) {
	/* Получаем максимальный номер для положения вершинного атрибута. */
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxVertexAttributes);
}

VertexLayout::~VertexLayout() {
	_attributes.clear();
}

void VertexLayout::enable() {
	BOOST_FOREACH(VertexAttribute & attrib, _attributes | boost::adaptors::map_values) {
		if (attrib.enabled) {
			Extensions::glEnableVertexAttribArrayARB(attrib.location);
			Extensions::glVertexAttribPointerARB(attrib.location, attrib.numComponents, TypeUtils::toGL(attrib.format), attrib.normalized, attrib.stride, attrib.offset);
		}
	}
}

void VertexLayout::disable() {
	BOOST_FOREACH(VertexAttribute & attrib, _attributes | boost::adaptors::map_values) {
		if (attrib.enabled)
			Extensions::glDisableVertexAttribArrayARB(attrib.location);
	}
}

void VertexLayout::setAttributes(VertexAttributeUmap_t attributes) {
	_attributes = attributes;
}

VertexAttributeUmap_t VertexLayout::getAttributes() {
	return _attributes;
}

void VertexLayout::setMaxVertexAttributes(int value) {
	_maxVertexAttributes = value;
}

int VertexLayout::getMaxVertexAttributes() {
	return _maxVertexAttributes;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
