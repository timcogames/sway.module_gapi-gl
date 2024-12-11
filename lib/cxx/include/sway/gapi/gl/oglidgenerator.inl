#include <sway/gapi/gl/oglidgenerator.hpp>

#include <algorithm>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

template <IdGeneratorType::Enum TYPE>
auto OGLIdGenerator<TYPE>::createInstance() -> IdGeneratorPtr_t {
  return new OGLIdGenerator();
}

template <IdGeneratorType::Enum TYPE>
OGLIdGenerator<TYPE>::OGLIdGenerator()
    : helper_(new OGLIdGeneratorHelper<TYPE>())
    , chunkCapacity_(BUFFER_IDS_CHUNK_CAPACITY) {}

template <IdGeneratorType::Enum TYPE>
OGLIdGenerator<TYPE>::OGLIdGenerator(OGLIdGeneratorHelper<TYPE> &helper)
    : helper_(&helper)
    , chunkCapacity_(BUFFER_IDS_CHUNK_CAPACITY) {}

template <IdGeneratorType::Enum TYPE>
OGLIdGenerator<TYPE>::~OGLIdGenerator() {
  helper_->release(used_.size(), used_.data());
  used_.clear();
}

template <IdGeneratorType::Enum TYPE>
auto OGLIdGenerator<TYPE>::getNextUid() -> ObjectUid_t {
  if (this->empty()) {
    auto *uids = new ObjectUid_t[chunkCapacity_];
    helper_->generate(used_.empty() ? 0 : *std::max_element(used_.begin(), used_.end()), chunkCapacity_, uids);

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
