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

auto OGLDrawCall::createInstance() -> DrawCallRef_t {
  auto instance = std::make_shared<OGLDrawCall>();
  return instance;
}

void OGLDrawCall::execute(TopologyType topology, BufferSet bufset, core::ValueDataType type) {
  if (bufset.ibo) {
    drawCbFunc_ = std::bind(&OGLDrawCall::drawIndexed_, this, std::placeholders::_1);
    drawElements_.mode = OGLDrawCall::topologyToGLenum(topology);
    drawElements_.count = bufset.ibo->getCapacity();
    drawElements_.type = TypeUtils::toGL(type);

    if (drawCbFunc_) {
      drawCbFunc_(bufset.ibo);
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

void OGLDrawCall::draw_([[maybe_unused]] BufferRef_t ibo) {
  if (drawArrays_.mode == GL_LINES) {
    glLineWidth(8);
  }

  glDrawArrays(drawArrays_.mode, drawArrays_.first, drawArrays_.count);
}

void OGLDrawCall::drawIndexed_(std::shared_ptr<Buffer> ibo) {
  ibo->bind();
  // if (OGLGenericBufferExtension::isBuffer(ibo->getUid().value())) {
  //   // OK
  // }

  glDrawElements(drawElements_.mode, drawElements_.count, drawElements_.type, nullptr);
  ibo->unbind();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
