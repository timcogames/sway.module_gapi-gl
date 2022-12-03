#include <sway/gapi/gl/buffer.hpp>
#include <sway/gapi/gl/drawcall.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

GLenum DrawCall::topologyToGLenum(TopologyType_t topology) {
  switch (topology) {
    case TopologyType_t::kPointList:
      return GL_POINTS;
    case TopologyType_t::kLineList:
      return GL_LINES;
    case TopologyType_t::kLineStrip:
      return GL_LINE_STRIP;
    case TopologyType_t::kTriangleList:
      return GL_TRIANGLES;
    case TopologyType_t::kTriangleStrip:
      return GL_TRIANGLE_STRIP;
    case TopologyType_t::kTriangleFan:
      return GL_TRIANGLE_FAN;
    default:
      return 0;
  }
}

auto DrawCall::createInstance() -> DrawCallRef_t {
  auto instance = std::make_shared<DrawCall>();
  return instance;
}

void DrawCall::execute(TopologyType_t topology, BufferSet bufset, core::ValueDataType type) {
  if (bufset.ibo) {
    _drawCbFunc = std::bind(&DrawCall::_drawIndexed, this, std::placeholders::_1);
    _drawElements.mode = DrawCall::topologyToGLenum(topology);
    _drawElements.count = bufset.ibo->getCapacity();
    _drawElements.type = TypeUtils::toGL(type);
  } else {
    _drawCbFunc = std::bind(&DrawCall::_draw, this, std::placeholders::_1);
    _drawArrays.mode = DrawCall::topologyToGLenum(topology);
    _drawArrays.first = 0;
    _drawArrays.count = bufset.vbo->getCapacity();
  }

  if (_drawCbFunc) {
    _drawCbFunc(bufset.ibo);
  }
}

void DrawCall::_draw(BufferRef_t ibo) {
  // boost::ignore_unused(ibo);
  glDrawArrays(_drawArrays.mode, _drawArrays.first, _drawArrays.count);
}

void DrawCall::_drawIndexed(BufferRef_t ibo) {
  if (Extension::glIsBuffer(ibo->getObjectId())) {
    // Empty
  }

  ibo->bind();
  glDrawElements(_drawElements.mode, _drawElements.count, _drawElements.type, nullptr);
  ibo->unbind();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
