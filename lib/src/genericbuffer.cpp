#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/genericbuffer.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto GenericBuffer::targetToGLenum(BufferTarget_t target) -> GLenum {
#ifdef _EMSCRIPTEN
  switch (target) {
    case BufferTarget_t::Array:
      return GL_ARRAY_BUFFER;
    case BufferTarget_t::ElementArray:
      return GL_ELEMENT_ARRAY_BUFFER;
    default:
      return 0;
  }
#else
  switch (target) {
    case BufferTarget_t::Array:
      return GL_ARRAY_BUFFER_ARB;
    case BufferTarget_t::ElementArray:
      return GL_ELEMENT_ARRAY_BUFFER_ARB;
    default:
      return 0;
  }
#endif
}

auto GenericBuffer::usageToGLenum(BufferUsage_t usage) -> GLenum {
#ifdef _EMSCRIPTEN
  switch (usage) {
    case BufferUsage_t::Static:
      return GL_STATIC_DRAW;
    case BufferUsage_t::Dynamic:
      return GL_DYNAMIC_DRAW;
    case BufferUsage_t::Stream:
      return GL_STREAM_DRAW;
    default:
      return 0;
  }
#else
  switch (usage) {
    case BufferUsage_t::Static:
      return GL_STATIC_DRAW_ARB;
    case BufferUsage_t::Dynamic:
      return GL_DYNAMIC_DRAW_ARB;
    case BufferUsage_t::Stream:
      return GL_STREAM_DRAW_ARB;
    default:
      return 0;
  }
#endif
}

auto GenericBuffer::accessToGLenum(BufferAccess_t access) -> GLenum {
#ifdef _EMSCRIPTEN
  switch (access) {
    case BufferAccess_t::Read:
      return GL_READ_ONLY;
    case BufferAccess_t::Write:
      return GL_WRITE_ONLY;
    case BufferAccess_t::ReadWrite:
      return GL_READ_WRITE;
    default:
      return 0;
  }
#else
  switch (access) {
    case BufferAccess_t::Read:
      return GL_READ_ONLY_ARB;
    case BufferAccess_t::Write:
      return GL_WRITE_ONLY_ARB;
    case BufferAccess_t::ReadWrite:
      return GL_READ_WRITE_ARB;
    default:
      return 0;
  }
#endif
}

auto GenericBuffer::createInstance(BufferIdQueueRef_t idQueue, const BufferCreateInfo &createInfo) -> BufferRef_t {
  auto instance = std::make_shared<GenericBuffer>(idQueue, createInfo.desc);
  if (instance->allocate(createInfo.data)) {
    return instance;
  }

  return nullptr;
}

using BufferObjectIdType = u32_t;

GenericBuffer::GenericBuffer(BufferIdQueueRef_t idQueue, const BufferDescriptor &desc)
    : Buffer(desc)
    , helper_(gapi::Extension::extensions)
    , target_(desc.target)
    , usage_(desc.usage)
    , capacity_(desc.capacity)
    , byteStride_(desc.byteStride) {
  setUid(idQueue->newGuid());
}

GenericBuffer::~GenericBuffer() {
  // auto objectId = getUid().value();
  // #ifdef _EMSCRIPTEN
  //   glDeleteBuffers(1, &objectId);
  // #else
  //   Extension::glDeleteBuffers(1, &objectId);
  // #endif
}

auto GenericBuffer::allocate(const void *data) -> bool {
  auto target = GenericBuffer::targetToGLenum(target_);
  auto dataSize = capacity_ * byteStride_;
  auto allocedSize = 0;

  helper_.BindBuffer(target, getUid().value());
  helper_.BufferData(target, dataSize, data, GenericBuffer::usageToGLenum(usage_));
  helper_.GetBufferParam(target, GL_BUFFER_SIZE_ARB, &allocedSize);

  return allocedSize == dataSize;
}

void GenericBuffer::updateSubdata(u32_t offset, u32_t size, const void *source) {
  auto target = GenericBuffer::targetToGLenum(target_);
  if (helper_.IsBuffer(getUid().value())) {
    helper_.BindBuffer(target, getUid().value());
    helper_.BufferSubData(target, offset, size, source);
    helper_.BindBuffer(target, 0);
  }
}

void GenericBuffer::updateSubdata(const void *source) { updateSubdata(0, capacity_ * byteStride_, source); }

void GenericBuffer::bind() { helper_.BindBuffer(GenericBuffer::targetToGLenum(target_), getUid().value()); }

void GenericBuffer::unbind() { helper_.BindBuffer(GenericBuffer::targetToGLenum(target_), 0); }

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
