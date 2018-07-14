#include <sway/gapi/vertexlayout.h>
#include <sway/gapi/extensions.h>

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

void VertexLayout::addAttribute(VertexSemantic_t semantic, Type_t format, s32_t numComponents) {
	std::string name = stringize(semantic);
	s32_t location = Extensions::glGetAttribLocationARB(_program->getId(), name.c_str());

	if (location >= 0 && location <= _maxVertexAttributes) {
		VertexAttribute attrib;
		attrib.location = location;
		attrib.semantic = semantic;
		attrib.format = format;
		attrib.numComponents = numComponents;
		attrib.stride = sizeof(f32_t) * numComponents;
		attrib.offset = BUFFER_OFFSET(_attributeOffset);
		attrib.normalized = false;
		attrib.enabled = true;

		_attributes.insert(std::make_pair(name, attrib));
		_attributeOffset += attrib.stride;
	}
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
