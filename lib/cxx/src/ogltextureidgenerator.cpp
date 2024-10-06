#include <sway/gapi/gl/ogltextureidgenerator.hpp>

#include <algorithm>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLTextureIdGenerator::createInstance() -> IdGeneratorPtr_t { return new OGLTextureIdGenerator(); }

OGLTextureIdGenerator::OGLTextureIdGenerator()
    : chunkCapacity_(TEXTURE_IDS_CHUNK_CAPACITY) {}

OGLTextureIdGenerator::~OGLTextureIdGenerator() {
  helper_.deleteTextures(used_.size(), used_.data());
  used_.clear();
}

auto OGLTextureIdGenerator::getNextUid() -> ObjectUid_t {
  if (this->empty()) {
    auto *uids = new ObjectUid_t[chunkCapacity_];
    helper_.generateTextures(used_.empty() ? 0 : *std::max_element(used_.begin(), used_.end()), chunkCapacity_, uids);

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
