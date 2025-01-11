#include <sway/gapi/gl/oglgenericbufferidgenerator.hpp>

#include <algorithm>

namespace sway::gapi {

auto OGLGenericBufferIdGenerator::createInstance() -> typedefs::IdGeneratorPtr_t {
  return new OGLGenericBufferIdGenerator();
}

OGLGenericBufferIdGenerator::OGLGenericBufferIdGenerator()
    : helper_(new OGLGenericBufferHelper())
    , chunkCapacity_(BUFFER_IDS_CHUNK_CAPACITY) {}

OGLGenericBufferIdGenerator::OGLGenericBufferIdGenerator(OGLGenericBufferHelperIface &helper)
    : helper_(&helper)
    , chunkCapacity_(BUFFER_IDS_CHUNK_CAPACITY) {}

OGLGenericBufferIdGenerator::~OGLGenericBufferIdGenerator() {
  helper_->deleteBuffers(used_.size(), used_.data());
  used_.clear();
}

auto OGLGenericBufferIdGenerator::getNextUid() -> ObjectUid_t {
  if (this->empty()) {
    auto *uids = new ObjectUid_t[chunkCapacity_];
    helper_->generateBuffers(used_.empty() ? 0 : *std::max_element(used_.begin(), used_.end()), chunkCapacity_, uids);

    // std::generate_n
    for (auto i = 0; i < chunkCapacity_; ++i) {
      this->push(uids[i]);
    }

    SAFE_DELETE_ARRAY(uids);
  }

  used_.push_back(this->front());
  this->pop();

  return used_.back();
}

}  // namespace sway::gapi
