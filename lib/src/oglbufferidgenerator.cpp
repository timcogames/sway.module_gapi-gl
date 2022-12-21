#include <sway/gapi/gl/oglbufferidgenerator.hpp>

#include <algorithm>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLBufferIdGenerator::createInstance() -> std::shared_ptr<IdGenerator> {
  return std::make_shared<OGLBufferIdGenerator>();
}

OGLBufferIdGenerator::OGLBufferIdGenerator()
    : helper_(gapi::Extension::extensions)
    , chunkCapacity_(BUFFER_IDS_CHUNK_CAPACITY) {}

OGLBufferIdGenerator::~OGLBufferIdGenerator() {
  helper_.DeleteBuffers(used_.size(), used_.data());
  used_.clear();
}

auto OGLBufferIdGenerator::newGuid() -> BufferIdType {
  if (this->empty()) {
    auto *bufferIds = new BufferIdType[chunkCapacity_];

    helper_.GenerateBuffers(
        used_.empty() ? 0 : *std::max_element(used_.begin(), used_.end()), chunkCapacity_, bufferIds);

    for (auto i = 0; i < chunkCapacity_; ++i) {
      this->push(bufferIds[i]);
    }

    SAFE_DELETE_ARRAY(bufferIds);
  }

  used_.push_back(this->front());
  this->pop();

  return used_.back();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
