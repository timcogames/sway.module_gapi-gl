#include <sway/gapi/gl/oglvertexarray.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLVertexArray::createInstance() -> VertexArrayPtr_t {
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

NS_END()  // namespace gapi
NS_END()  // namespace sway
