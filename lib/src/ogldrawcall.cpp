#include <sway/gapi/gl/ogldrawcall.hpp>
#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/oglgenericbuffer.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

GLenum OGLDrawCall::topologyToGLenum(TopologyType topology) {
  switch (topology) {
    case TopologyType::POINT_LIST:
      return GL_POINTS;
    case TopologyType::LINE_LIST:
      return GL_LINES;
    case TopologyType::LINE_STRIP:
      return GL_LINE_STRIP;
    case TopologyType::TRIANGLE_LIST:
      return GL_TRIANGLES;
    case TopologyType::TRIANGLE_STRIP:
      return GL_TRIANGLE_STRIP;
    case TopologyType::TRIANGLE_FAN:
      return GL_TRIANGLE_FAN;
    default:
      return 0;
  }
}

auto OGLDrawCall::createInstance() -> DrawCallRef_t {
  auto instance = std::make_shared<OGLDrawCall>();
  return instance;
}

void OGLDrawCall::execute(TopologyType topology, BufferSet bufset, core::ValueDataType type) {
  if (bufset.ibo) {
    _drawCbFunc = std::bind(&OGLDrawCall::drawIndexed_, this, std::placeholders::_1);
    _drawElements.mode = OGLDrawCall::topologyToGLenum(topology);
    _drawElements.count = bufset.ibo->getCapacity();
    _drawElements.type = TypeUtils::toGL(type);
  } else {
    _drawCbFunc = std::bind(&OGLDrawCall::draw_, this, std::placeholders::_1);
    _drawArrays.mode = OGLDrawCall::topologyToGLenum(topology);
    _drawArrays.first = 0;
    _drawArrays.count = bufset.vbo->getCapacity();
  }

  if (_drawCbFunc) {
    _drawCbFunc(bufset.ibo);
  }
}

void OGLDrawCall::draw_([[maybe_unused]] BufferRef_t ibo) {
  glDrawArrays(_drawArrays.mode, _drawArrays.first, _drawArrays.count);
}

void OGLDrawCall::drawIndexed_(std::shared_ptr<Buffer> ibo) {
  ibo->bind();
  if (Extension::glIsBuffer(ibo->getUid().value())) {
    // OK
  }

  glDrawElements(_drawElements.mode, _drawElements.count, _drawElements.type, nullptr);
  ibo->unbind();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
