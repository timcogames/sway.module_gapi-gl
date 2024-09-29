#include <sway/gapi/gl/ogltextureidgenerator.hpp>

#include <algorithm>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLTextureIdGenerator::createInstance() -> IdGeneratorPtr_t { return new OGLTextureIdGenerator(); }

OGLTextureIdGenerator::OGLTextureIdGenerator()
    : chunkCapacity_(TEXTURE_IDS_CHUNK_CAPACITY) {}

OGLTextureIdGenerator::~OGLTextureIdGenerator() {
  helper_.deleteTextures(used_.size(), used_.data());
  used_.clear();
}

auto OGLTextureIdGenerator::getNextUid() -> TextureIdType {
  if (this->empty()) {
    auto *bufferIds = new TextureIdType[chunkCapacity_];

    helper_.generateTextures(
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
