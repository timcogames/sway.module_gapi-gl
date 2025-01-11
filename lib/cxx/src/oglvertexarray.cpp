#include <sway/gapi/gl/oglvertexarray.hpp>

namespace sway::gapi {

auto OGLVertexArray::createInstance() -> typedefs::VertexArrayPtr_t {
  auto *instance = new OGLVertexArray();
  return instance;
}

OGLVertexArray::OGLVertexArray() { helper_.generateVertexArrays(1, &objname_); }

OGLVertexArray::~OGLVertexArray() {
  if (helper_.isVertexArray(objname_)) {
    helper_.deleteVertexArrays(1, &objname_);
  }
}

void OGLVertexArray::bind() { helper_.bindVertexArray(objname_); }

void OGLVertexArray::unbind() { helper_.bindVertexArray(0); }

}  // namespace sway::gapi
