#include <sway/gapi/gl/oglvertexattriblayout.hpp>

namespace sway::gapi {

auto OGLVertexAttribLayout::createInstance(typedefs::ShaderProgramPtr_t program) -> typedefs::VertexAttribLayoutPtr_t {
  auto *instance = new OGLVertexAttribLayout(program);
  return instance;
}

OGLVertexAttribLayout::OGLVertexAttribLayout(typedefs::ShaderProgramPtr_t program)
    : program_(program)
    , attribOffset_(0) {
  // Получаем максимальный номер для положения вершинного атрибута.
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs_);
}

OGLVertexAttribLayout::~OGLVertexAttribLayout() { attribs_.clear(); }

void OGLVertexAttribLayout::addAttribute(VertexAttribDescriptor desc) {
  auto vtxShader = program_->getShader(ShaderType::Enum::VERT);
  auto const alias = stringize(desc.semantic);

  desc.location = vtxShader->getAttribLocation(program_->getUniqueId(), alias.c_str());
  desc.pointer = BUFFER_OFFSET(attribOffset_);

  if (desc.location >= 0 && desc.location <= maxVertexAttribs_) {
    attribs_.insert(std::make_pair(alias, desc));
    attribOffset_ += desc.stride;
  }
}

void OGLVertexAttribLayout::enable() {
  for (const auto &attrib : attribs_) {
    if (attrib.second.enabled) {
      helper_.enableArray((u32_t)attrib.second.location);
      helper_.setup((u32_t)attrib.second.location, attrib.second.numComponents, TypeUtils::toGL(attrib.second.format),
          (s8_t)attrib.second.normalized, (i32_t)attribOffset_, attrib.second.pointer);
    }
  }
}

void OGLVertexAttribLayout::disable() {
  for (const auto &attrib : attribs_) {
    if (attrib.second.enabled) {
      helper_.disableArray((u32_t)attrib.second.location);
    }
  }
}

}  // namespace sway::gapi
