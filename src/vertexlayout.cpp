#include <sway/gapi/gl/vertexlayout.h>
#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

VertexLayoutRef_t VertexLayout::createInstance(ShaderProgramRef_t program) {
	auto instance = std::make_shared<VertexLayout>(program);
	return instance;
}

VertexLayout::VertexLayout(ShaderProgramRef_t program) : IVertexLayoutBase(program)
	, _attributeOffset(0)
	, _shaderProgram(program) {
	/* Получаем максимальный номер для положения вершинного атрибута. */
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxVertexAttributes);
}

VertexLayout::~VertexLayout() {
	_attributes.clear();
}

void VertexLayout::addAttribute(VertexAttributeDescriptor desc) {
	std::string alias = stringize(desc.semantic);
	s32_t location = Extension::glGetAttribLocation(_shaderProgram->getObjectId(), alias.c_str());

	desc.location = location;
	desc.pointer = BUFFER_OFFSET(_attributeOffset);

	if (location >= 0 && location <= _maxVertexAttributes) {
		_attributes.insert(std::make_pair(alias, desc));
		_attributeOffset += desc.stride;
	}
}

void VertexLayout::enable() {
	BOOST_FOREACH (VertexAttributeDescriptor & attrib, _attributes | boost::adaptors::map_values) {
		if (attrib.enabled) {
			Extension::glEnableVertexAttribArray(attrib.location);
			Extension::glVertexAttribPointer(attrib.location, attrib.numComponents, TypeUtils::toGL(attrib.format), attrib.normalized, _attributeOffset, attrib.pointer);
		}
	}
}

void VertexLayout::disable() {
	BOOST_FOREACH (VertexAttributeDescriptor & attrib, _attributes | boost::adaptors::map_values) {
		if (attrib.enabled)
			Extension::glDisableVertexAttribArray(attrib.location);
	}
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
