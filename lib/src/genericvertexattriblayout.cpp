#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/genericvertexattriblayout.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto GenericVertexAttribLayout::createInstance(ShaderProgramRef_t program) -> VertexAttribLayoutPtr_t {
  auto instance = std::make_shared<GenericVertexAttribLayout>(program);
  return instance;
}

GenericVertexAttribLayout::GenericVertexAttribLayout(ShaderProgramRef_t program)
    : VertexAttribLayout(program)
    , shaderHelper_(gapi::Extension::extensions)
    , vertexAttribHelper_(gapi::Extension::extensions)
    , shaderProgram_(program)
    , attributeOffset_(0) {
  // Получаем максимальный номер для положения вершинного атрибута.
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes_);
}

GenericVertexAttribLayout::~GenericVertexAttribLayout() { attributes_.clear(); }

void GenericVertexAttribLayout::addAttribute(VertexAttributeDescriptor desc) {
  std::string const alias = stringize(desc.semantic);

  desc.location = shaderHelper_.GetAttribLocation(shaderProgram_->getUid().value(), alias.c_str());
  desc.pointer = BUFFER_OFFSET(attributeOffset_);

  if (desc.location >= 0 && desc.location <= maxVertexAttributes_) {
    attributes_.insert(std::make_pair(alias, desc));
    attributeOffset_ += desc.stride;
  }
}

void GenericVertexAttribLayout::enable() {
  for (const auto &attrib : attributes_) {
    if (attrib.second.enabled) {
      vertexAttribHelper_.EnableArray((u32_t)attrib.second.location);
      vertexAttribHelper_.Setup((u32_t)attrib.second.location, attrib.second.numComponents,
          TypeUtils::toGL(attrib.second.format), (s8_t)attrib.second.normalized, (s32_t)attributeOffset_,
          attrib.second.pointer);
    }
  }
}

void GenericVertexAttribLayout::disable() {
  for (const auto &attrib : attributes_) {
    if (attrib.second.enabled) {
      vertexAttribHelper_.DisableArray((u32_t)attrib.second.location);
    }
  }
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
