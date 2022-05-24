#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/vertexlayout.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

VertexLayoutRef_t VertexLayout::createInstance(ShaderProgramRef_t program) {
  auto instance = std::make_shared<VertexLayout>(program);
  return instance;
}

VertexLayout::VertexLayout(ShaderProgramRef_t program)
    : IVertexLayoutBase(program)
    , _shaderProgram(program)
    , _attributeOffset(0) {
  /* Получаем максимальный номер для положения вершинного атрибута. */
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxVertexAttributes);
}

VertexLayout::~VertexLayout() { _attributes.clear(); }

void VertexLayout::addAttribute(VertexAttributeDescriptor desc) {
  std::string alias = stringize(desc.semantic);

#ifdef _EMSCRIPTEN
  s32_t location = glGetAttribLocation(_shaderProgram->getObjectId(), alias.c_str());
#else
  s32_t location = Extension::glGetAttribLocation(_shaderProgram->getObjectId(), alias.c_str());
#endif

  desc.location = location;
  desc.pointer = BUFFER_OFFSET(_attributeOffset);

  if (location >= 0 && location <= _maxVertexAttributes) {
    _attributes.insert(std::make_pair(alias, desc));
    _attributeOffset += desc.stride;
  }
}

void VertexLayout::enable() {
  for (const auto &attrib : _attributes) {
    if (attrib.second.enabled) {
#ifdef _EMSCRIPTEN
      glEnableVertexAttribArray(attrib.second.location);
      glVertexAttribPointer(attrib.second.location, attrib.second.numComponents, TypeUtils::toGL(attrib.second.format),
          attrib.second.normalized, _attributeOffset, attrib.second.pointer);
#else
      Extension::glEnableVertexAttribArray(attrib.second.location);
      Extension::glVertexAttribPointer(attrib.second.location, attrib.second.numComponents,
          TypeUtils::toGL(attrib.second.format), attrib.second.normalized, _attributeOffset, attrib.second.pointer);
#endif
    }
  }
}

void VertexLayout::disable() {
  for (const auto &attrib : _attributes) {
    if (attrib.second.enabled) {
#ifdef _EMSCRIPTEN
      glDisableVertexAttribArray(attrib.second.location);
#else
      Extension::glDisableVertexAttribArray(attrib.second.location);
#endif
    }
  }
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
