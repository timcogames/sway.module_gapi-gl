#include <sway/gapi/gl/oglbuffermapaccessconvertor.hpp>
#include <sway/gapi/gl/oglbuffermaprangeaccessconvertor.hpp>
#include <sway/gapi/gl/oglbuffertargetconvertor.hpp>
#include <sway/gapi/gl/oglgenericbuffer.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLGenericBuffer::usageToGLenum(BufferUsage usage) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
  switch (usage) {
    case BufferUsage::STATIC:
      return GL_STATIC_DRAW;
    case BufferUsage::DYNAMIC:
      return GL_DYNAMIC_DRAW;
    case BufferUsage::STREAM:
      return GL_STREAM_DRAW;
    default:
      return 0;
  }
#else
  switch (usage) {
    case BufferUsage::STATIC:
      return GL_STATIC_DRAW_ARB;
    case BufferUsage::DYNAMIC:
      return GL_DYNAMIC_DRAW_ARB;
    case BufferUsage::STREAM:
      return GL_STREAM_DRAW_ARB;
    default:
      return 0;
  }
#endif
}

auto OGLGenericBuffer::createInstance(IdGeneratorPtr_t idQueue, const BufferCreateInfo &createInfo) -> BufferPtr_t {
  auto *instance = new OGLGenericBuffer(idQueue, createInfo.desc);
  if (instance->allocate(createInfo.data)) {
    return instance;
  }

  return nullptr;
}

using BufferObjectIdType = u32_t;

OGLGenericBuffer::OGLGenericBuffer(IdGeneratorPtr_t idQueue, const BufferDescriptor &desc)
    : Buffer(desc)
    , target_(desc.target)
    , usage_(desc.usage)
    , capacity_(desc.capacity)
    , byteStride_(desc.byteStride) {
  setUid(idQueue->newGuid());
}

auto OGLGenericBuffer::allocate(const void *data) -> bool {
  auto dataSize = capacity_ * byteStride_;
  auto allocedSize = 0;

  this->bind();
  helper_.bufferData(target_, dataSize, data, OGLGenericBuffer::usageToGLenum(usage_));
  helper_.getBufferParam(target_, GL_BUFFER_SIZE_ARB, &allocedSize);

  return allocedSize == dataSize;
}

void OGLGenericBuffer::updateSubdata(BufferSubdataDescriptor desc) {
  if (!helper_.isBuffer(getUid().value())) {
    return;
  }

  this->bind();
  helper_.bufferSubData(target_, desc.offset, desc.size, desc.data);
  this->unbind();
}

void OGLGenericBuffer::updateSubdata(const void *src) {
  BufferSubdataDescriptor desc;
  desc.offset = 0;
  desc.size = capacity_ * byteStride_;
  desc.data = src;
  this->updateSubdata(desc);
}

void OGLGenericBuffer::flush(i32_t offset, i32_t length) { helper_.flush(target_, offset, length); }

auto OGLGenericBuffer::map(BufferMapAccess flags) -> void * {
  if (!helper_.isBuffer(getUid().value())) {
    return nullptr;
  }

  this->bind();
  // clang-format off
  void *data = helper_.mapBuffer(target_, 
    OGLBufferMapAccessConvertor::toGLenum(flags));  // clang-format on
  this->unbind();
  return data;
}

auto OGLGenericBuffer::mapRange(
    i32_t offset, i32_t length, core::detail::EnumClassBitset<BufferMapRangeAccess> bitset) -> void * {
  if (!helper_.isBuffer(getUid().value())) {
    return nullptr;
  }

  auto flags = 0;
  if (bitset.has(BufferMapRangeAccess::WRITE)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::WRITE);
  }

  if (bitset.has(BufferMapRangeAccess::READ)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::READ);
  }

  if (bitset.has(BufferMapRangeAccess::INVALIDATE_RANGE)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::INVALIDATE_RANGE);
  }

  if (bitset.has(BufferMapRangeAccess::INVALIDATE_BUFFER)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::INVALIDATE_BUFFER);
  }

  if (bitset.has(BufferMapRangeAccess::FLUSH_EXPLICIT)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::FLUSH_EXPLICIT);
  }

  if (bitset.has(BufferMapRangeAccess::UNSYNCHRONIZED)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::UNSYNCHRONIZED);
  }

  this->bind();
  void *mapped = helper_.mapBufferRange(target_, offset, length, flags);
  if (mapped == nullptr) {
    std::cout << "[ERR]: Mapping buffer range" << std::endl;
  }
  this->unbind();

  return mapped;
}

void OGLGenericBuffer::unmap() {
  this->bind();
  if (helper_.unmapBuffer(target_) == GL_FALSE) {
    std::cout << "[ERR]: Unmapping buffer" << std::endl;
  }

  this->unbind();
}

void OGLGenericBuffer::bindRange(u32_t buffer, ptrdiff_t offset, ptrdiff_t size) {
  // GL_TRANSFORM_FEEDBACK_BUFFER or GL_UNIFORM_BUFFER
  helper_.bindBufferRange(target_, getUid().value(), buffer, offset, size);
}

void OGLGenericBuffer::bind() { helper_.bindBuffer(target_, getUid().value()); }

void OGLGenericBuffer::unbind() { helper_.bindBuffer(target_, 0); }

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
