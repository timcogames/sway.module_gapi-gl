#include <sway/gapi/gl/oglvertexattriblayout.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLVertexAttribLayout::createInstance(ShaderProgramRef_t program) -> VertexAttribLayoutPtr_t {
  auto instance = std::make_shared<OGLVertexAttribLayout>(program);
  return instance;
}

OGLVertexAttribLayout::OGLVertexAttribLayout(ShaderProgramRef_t program)
    : program_(program)
    , attribOffset_(0) {
  // Получаем максимальный номер для положения вершинного атрибута.
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs_);
}

OGLVertexAttribLayout::~OGLVertexAttribLayout() { attribs_.clear(); }

void OGLVertexAttribLayout::addAttribute(VertexAttribDescriptor desc) {
  auto vtxShader = program_->getShader(ShaderType::VERT);
  auto const alias = stringize(desc.semantic);

  desc.location = vtxShader->getAttribLocation(program_->getUid(), alias.c_str());
  desc.pointer = BUFFER_OFFSET(attribOffset_);

  if (desc.location >= 0 && desc.location <= maxVertexAttribs_) {
    attribs_.insert(std::make_pair(alias, desc));
    attribOffset_ += desc.stride;
  }
}

void OGLVertexAttribLayout::enable() {
  for (const auto &attrib : attribs_) {
    if (attrib.second.enabled) {
      helper_.EnableArray((u32_t)attrib.second.location);
      helper_.Setup((u32_t)attrib.second.location, attrib.second.numComponents, TypeUtils::toGL(attrib.second.format),
          (s8_t)attrib.second.normalized, (s32_t)attribOffset_, attrib.second.pointer);
    }
  }
}

void OGLVertexAttribLayout::disable() {
  for (const auto &attrib : attribs_) {
    if (attrib.second.enabled) {
      helper_.DisableArray((u32_t)attrib.second.location);
    }
  }
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
