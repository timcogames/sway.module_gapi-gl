#include <sway/gapi/gl/oglgenericbuffer.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLGenericBuffer::targetToGLenum(BufferTarget target) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
  switch (target) {
    case BufferTarget::ARRAY:
      return GL_ARRAY_BUFFER;
    case BufferTarget::ELEMENT_ARRAY:
      return GL_ELEMENT_ARRAY_BUFFER;
    default:
      return 0;
  }
#else
  switch (target) {
    case BufferTarget::ARRAY:
      return GL_ARRAY_BUFFER_ARB;
    case BufferTarget::ELEMENT_ARRAY:
      return GL_ELEMENT_ARRAY_BUFFER_ARB;
    default:
      return 0;
  }
#endif
}

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

auto OGLGenericBuffer::accessToGLenum(BufferAccess access) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
  switch (access) {
    case BufferAccess::READ:
      return GL_READ_ONLY;
    case BufferAccess::WRITE:
      return GL_WRITE_ONLY;
    case BufferAccess::READ_WRITE:
      return GL_READ_WRITE;
    default:
      return 0;
  }
#else
  switch (access) {
    case BufferAccess::READ:
      return GL_READ_ONLY_ARB;
    case BufferAccess::WRITE:
      return GL_WRITE_ONLY_ARB;
    case BufferAccess::READ_WRITE:
      return GL_READ_WRITE_ARB;
    default:
      return 0;
  }
#endif
}

auto OGLGenericBuffer::createInstance(IdGeneratorRef_t idQueue, const BufferCreateInfo &createInfo) -> BufferRef_t {
  auto instance = std::make_shared<OGLGenericBuffer>(idQueue, createInfo.desc);
  if (instance->allocate(createInfo.data)) {
    return instance;
  }

  return nullptr;
}

using BufferObjectIdType = u32_t;

OGLGenericBuffer::OGLGenericBuffer(IdGeneratorRef_t idQueue, const BufferDescriptor &desc)
    : Buffer(desc)
    , target_(desc.target)
    , usage_(desc.usage)
    , capacity_(desc.capacity)
    , byteStride_(desc.byteStride) {
  setUid(idQueue->newGuid());
}

auto OGLGenericBuffer::allocate(const void *data) -> bool {
  auto target = OGLGenericBuffer::targetToGLenum(target_);
  auto dataSize = capacity_ * byteStride_;
  auto allocedSize = 0;

  this->bind();
  helper_.bufferData(target, dataSize, data, OGLGenericBuffer::usageToGLenum(usage_));
  helper_.getBufferParam(target, GL_BUFFER_SIZE_ARB, &allocedSize);

  return allocedSize == dataSize;
}

void OGLGenericBuffer::updateSubdata(u32_t offset, u32_t size, const void *src) {
  if (!helper_.isBuffer(getUid().value())) {
    return;
  }

  this->bind();
  helper_.bufferSubData(OGLGenericBuffer::targetToGLenum(target_), offset, size, src);
  this->unbind();
}

void OGLGenericBuffer::updateSubdata(const void *src) { updateSubdata(0, capacity_ * byteStride_, src); }

auto OGLGenericBuffer::map() -> void * {
  if (!helper_.isBuffer(getUid().value())) {
    return nullptr;
  }

  this->bind();
  // clang-format off
  void *data = helper_.mapBuffer(OGLGenericBuffer::targetToGLenum(target_),
      OGLGenericBuffer::accessToGLenum(BufferAccess::WRITE));  // clang-format on
  this->unbind();

  return data;
}

auto OGLGenericBuffer::mapRange(s32_t offset, s32_t length, BufferAccess flags) -> void * {
  if (!helper_.isBuffer(getUid().value())) {
    return nullptr;
  }

  this->bind();
  // clang-format off
  void *data = helper_.mapRange(offset, length, OGLGenericBuffer::targetToGLenum(target_),
      OGLGenericBuffer::accessToGLenum(flags));  // clang-format on
  this->unbind();

  return data;
}

void OGLGenericBuffer::unmap() {
  this->bind();
  helper_.unmapBuffer(OGLGenericBuffer::targetToGLenum(target_));
  this->unbind();
}

void OGLGenericBuffer::bind() { helper_.bindBuffer(OGLGenericBuffer::targetToGLenum(target_), getUid().value()); }

void OGLGenericBuffer::unbind() { helper_.bindBuffer(OGLGenericBuffer::targetToGLenum(target_), 0); }

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
