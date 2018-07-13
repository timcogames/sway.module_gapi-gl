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
		VertexAttribute attribute;
		attribute.location = location;
		attribute.semantic = semantic;
		attribute.format = format;
		attribute.numComponents = numComponents;
		attribute.stride = sizeof(f32_t) * numComponents;
		attribute.offset = BUFFER_OFFSET(_attributeOffset);
		attribute.normalized = false;
		attribute.enabled = true;

		_attributes.insert(std::make_pair(name, attribute));
		_attributeOffset += attribute.stride;
	}
}

void VertexLayout::enable() {
	BOOST_FOREACH(VertexAttribute & attribute, _attributes | boost::adaptors::map_values) { 
		Extensions::glEnableVertexAttribArrayARB(attribute.location);
		Extensions::glVertexAttribPointerARB(attribute.location, attribute.numComponents, TypeUtils::toGL(attribute.format), attribute.normalized, attribute.stride, attribute.offset);
	}
}

void VertexLayout::disable() {
	BOOST_FOREACH(VertexAttribute & attribute, _attributes | boost::adaptors::map_values)
		Extensions::glDisableVertexAttribArrayARB(attribute.location);
}

void VertexLayout::setAttributes(VertexAttributeUmap_t attributes) {
	_attributes = attributes;
}

VertexAttributeUmap_t VertexLayout::getAttributes() {
	return _attributes;
}

void VertexLayout::setMaxVertexAttributes(int maxVertexAttributes) {
	_maxVertexAttributes = maxVertexAttributes;
}

int VertexLayout::getMaxVertexAttributes() {
	return _maxVertexAttributes;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
