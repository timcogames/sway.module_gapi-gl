#include <sway/gapi/gl/oglframebufferidgenerator.hpp>

#include <algorithm>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLFrameBufferIdGenerator::createInstance() -> IdGeneratorPtr_t { return new OGLFrameBufferIdGenerator(); }

OGLFrameBufferIdGenerator::OGLFrameBufferIdGenerator()
    : helper_(new OGLFrameBufferHelper())
    , chunkCapacity_(BUFFER_IDS_CHUNK_CAPACITY) {}

OGLFrameBufferIdGenerator::OGLFrameBufferIdGenerator(OGLFrameBufferHelperIface &helper)
    : helper_(&helper)
    , chunkCapacity_(BUFFER_IDS_CHUNK_CAPACITY) {}

OGLFrameBufferIdGenerator::~OGLFrameBufferIdGenerator() {
  helper_->deleteFramebuffers(used_.size(), used_.data());
  used_.clear();
}

auto OGLFrameBufferIdGenerator::getNextUid() -> ObjectUid_t {
  if (this->empty()) {
    auto *uids = new ObjectUid_t[chunkCapacity_];
    helper_->generateFramebuffers(
        used_.empty() ? 0 : *std::max_element(used_.begin(), used_.end()), chunkCapacity_, uids);

    for (auto i = 0; i < chunkCapacity_; ++i) {
      this->push(uids[i]);
    }

    SAFE_DELETE_ARRAY(uids);
  }

  used_.push_back(this->front());
  this->pop();

  return used_.back();
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
