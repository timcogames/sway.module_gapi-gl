#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/oglvertexattriblayout.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLVertexAttribLayout::createInstance(ShaderProgramRef_t program) -> VertexAttribLayoutPtr_t {
  auto instance = std::make_shared<OGLVertexAttribLayout>(program);
  return instance;
}

OGLVertexAttribLayout::OGLVertexAttribLayout(ShaderProgramRef_t program)
    : VertexAttribLayout(program)
    , shaderHelper_(gapi::Extension::extensions)
    , helper_(gapi::Extension::extensions)
    , shaderProgram_(program)
    , attributeOffset_(0) {
  // Получаем максимальный номер для положения вершинного атрибута.
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes_);
}

OGLVertexAttribLayout::~OGLVertexAttribLayout() { attributes_.clear(); }

void OGLVertexAttribLayout::addAttribute(VertexAttributeDescriptor desc) {
  std::string const alias = stringize(desc.semantic);

  desc.location = shaderHelper_.GetAttribLocation(shaderProgram_->getUid().value(), alias.c_str());
  desc.pointer = BUFFER_OFFSET(attributeOffset_);

  if (desc.location >= 0 && desc.location <= maxVertexAttributes_) {
    attributes_.insert(std::make_pair(alias, desc));
    attributeOffset_ += desc.stride;
  }
}

void OGLVertexAttribLayout::enable() {
  for (const auto &attrib : attributes_) {
    if (attrib.second.enabled) {
      helper_.EnableArray((u32_t)attrib.second.location);
      helper_.Setup((u32_t)attrib.second.location, attrib.second.numComponents, TypeUtils::toGL(attrib.second.format),
          (s8_t)attrib.second.normalized, (s32_t)attributeOffset_, attrib.second.pointer);
    }
  }
}

void OGLVertexAttribLayout::disable() {
  for (const auto &attrib : attributes_) {
    if (attrib.second.enabled) {
      helper_.DisableArray((u32_t)attrib.second.location);
    }
  }
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
