#include <sway/gapi/gl/ogldrawcall.hpp>
#include <sway/gapi/gl/oglgenericbuffer.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLDrawCall::topologyToGLenum(TopologyType topology) -> GLenum {
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

auto OGLDrawCall::createInstance() -> DrawCallPtr_t {
  auto *instance = new OGLDrawCall();
  return instance;
}

void OGLDrawCall::execute(TopologyType topology, BufferSet bufset, core::ValueDataType type) {
  if (bufset.ebo) {
    drawCbFunc_ = std::bind(&OGLDrawCall::drawIndexed_, this, std::placeholders::_1);
    drawElements_.mode = OGLDrawCall::topologyToGLenum(topology);
    drawElements_.count = bufset.ebo->getCapacity();
    drawElements_.type = TypeUtils::toGL(type);

    if (drawCbFunc_) {
      drawCbFunc_(bufset.ebo);
    }
  } else {
    drawCbFunc_ = std::bind(&OGLDrawCall::draw_, this, std::placeholders::_1);
    drawArrays_.mode = OGLDrawCall::topologyToGLenum(topology);
    drawArrays_.first = 0;
    drawArrays_.count = bufset.vbo->getCapacity();

    if (drawCbFunc_) {
      drawCbFunc_(nullptr);
    }
  }
}

void OGLDrawCall::draw_([[maybe_unused]] BufferPtr_t ebo) {
  if (drawArrays_.mode == GL_LINES) {
    glLineWidth(8);
  }

  glDrawArrays(drawArrays_.mode, drawArrays_.first, drawArrays_.count);
}

void OGLDrawCall::drawIndexed_(BufferPtr_t ebo) {
  ebo->bind();
  // if (OGLGenericBufferExtension::isBuffer(ebo->getUid().value())) {
  //   // OK
  // }

  glDrawElements(drawElements_.mode, drawElements_.count, drawElements_.type, nullptr);
  ebo->unbind();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
