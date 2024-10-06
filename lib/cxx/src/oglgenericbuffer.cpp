#include <sway/gapi/gl/oglbuffermapaccessconvertor.hpp>
#include <sway/gapi/gl/oglbuffermaprangeaccessconvertor.hpp>
#include <sway/gapi/gl/oglbuffertargetconvertor.hpp>
#include <sway/gapi/gl/oglgenericbuffer.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLGenericBuffer::usageToGLenum(BufferUsage::Enum usage) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
  switch (usage) {
    case BufferUsage::Enum::STATIC:
      return GL_STATIC_DRAW;
    case BufferUsage::Enum::DYNAMIC:
      return GL_DYNAMIC_DRAW;
    case BufferUsage::Enum::STREAM:
      return GL_STREAM_DRAW;
    default:
      return 0;
  }
#else
  switch (usage) {
    case BufferUsage::Enum::STATIC:
      return GL_STATIC_DRAW_ARB;
    case BufferUsage::Enum::DYNAMIC:
      return GL_DYNAMIC_DRAW_ARB;
    case BufferUsage::Enum::STREAM:
      return GL_STREAM_DRAW_ARB;
    default:
      return 0;
  }
#endif
}

auto OGLGenericBuffer::createInstance(IdGeneratorPtr_t idgen, const BufferCreateInfo &createInfo) -> BufferPtr_t {
  auto *instance = new OGLGenericBuffer(idgen, createInfo.desc);
  if (instance->allocate(createInfo.data)) {
    return instance;
  }

  return nullptr;
}

OGLGenericBuffer::OGLGenericBuffer(IdGeneratorPtr_t idgen, const BufferDescriptor &desc)
    : Buffer(desc)
    , target_(desc.target)
    , usage_(desc.usage)
    , capacity_(desc.capacity)
    , byteStride_(desc.byteStride) {
  setUid(idgen->getNextUid());
}

auto OGLGenericBuffer::allocate(const void *data) -> bool {
  auto dataSize = capacity_ * byteStride_;
  auto allocedSize = 0;

  bind();
  helper_.bufferData(target_, dataSize, data, OGLGenericBuffer::usageToGLenum(usage_));
  helper_.getBufferParam(target_, GL_BUFFER_SIZE_ARB, &allocedSize);

  return allocedSize == dataSize;
}

void OGLGenericBuffer::updateSubdata(BufferSubdataDescriptor desc) {
  if (!helper_.isBuffer(getUid())) {
    return;
  }

  bind();
  helper_.bufferSubData(target_, desc.offset, desc.size, desc.data);
  unbind();
}

void OGLGenericBuffer::updateSubdata(const void *src) {
  BufferSubdataDescriptor desc;
  desc.offset = 0;
  desc.size = capacity_ * byteStride_;
  desc.data = src;
  this->updateSubdata(desc);
}

void OGLGenericBuffer::flush(i32_t offset, i32_t len) { helper_.flush(target_, offset, len); }

auto OGLGenericBuffer::map(BufferMapAccess::Enum flags) -> void * {
  if (!helper_.isBuffer(getUid())) {
    return nullptr;
  }

  bind();
  void *data = helper_.mapBuffer(target_, OGLBufferMapAccessConvertor::toGLenum(flags));
  unbind();

  return data;
}

auto OGLGenericBuffer::mapRange(
    i32_t offset, i32_t len, core::detail::EnumClassBitset<BufferMapRangeAccess::Enum> bitset) -> void * {
  if (!helper_.isBuffer(getUid())) {
    return nullptr;
  }

  auto flags = 0;
  if (bitset.has(BufferMapRangeAccess::Enum::WRITE)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::Enum::WRITE);
  }

  if (bitset.has(BufferMapRangeAccess::Enum::READ)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::Enum::READ);
  }

  if (bitset.has(BufferMapRangeAccess::Enum::INVALIDATE_RANGE)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::Enum::INVALIDATE_RANGE);
  }

  if (bitset.has(BufferMapRangeAccess::Enum::INVALIDATE_BUFFER)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::Enum::INVALIDATE_BUFFER);
  }

  if (bitset.has(BufferMapRangeAccess::Enum::FLUSH_EXPLICIT)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::Enum::FLUSH_EXPLICIT);
  }

  if (bitset.has(BufferMapRangeAccess::Enum::UNSYNCHRONIZED)) {
    flags |= OGLBufferMapRangeAccessConvertor::toGLenum(BufferMapRangeAccess::Enum::UNSYNCHRONIZED);
  }

  bind();
  void *mapped = helper_.mapBufferRange(target_, offset, len, flags);
  if (mapped == nullptr) {
    std::cout << "[ERR]: Mapping buffer range" << std::endl;
  }
  unbind();

  return mapped;
}

void OGLGenericBuffer::unmap() {
  this->bind();
  if (helper_.unmapBuffer(target_) == GL_FALSE) {
    std::cout << "[ERR]: Unmapping buffer" << std::endl;
  }

  this->unbind();
}

void OGLGenericBuffer::bindRange(u32_t buf, ptrdiff_t offset, ptrdiff_t size) {
  // GL_TRANSFORM_FEEDBACK_BUFFER or GL_UNIFORM_BUFFER
  helper_.bindBufferRange(target_, getUid().value(), buf, offset, size);
}

void OGLGenericBuffer::bind() { helper_.bindBuffer(target_, getUid()); }

void OGLGenericBuffer::unbind() { helper_.bindBuffer(target_, 0); }

NS_END()  // namespace gapi
NS_END()  // namespace sway
