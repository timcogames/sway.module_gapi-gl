#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/oglgenericbuffer.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLGenericBuffer::targetToGLenum(BufferTarget target) -> GLenum {
#ifdef _EMSCRIPTEN
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
#ifdef _EMSCRIPTEN
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
#ifdef _EMSCRIPTEN
  switch (access) {
    case BufferAccess::Read:
      return GL_READ_ONLY;
    case BufferAccess::Write:
      return GL_WRITE_ONLY;
    case BufferAccess::ReadWrite:
      return GL_READ_WRITE;
    default:
      return 0;
  }
#else
  switch (access) {
    case BufferAccess::Read:
      return GL_READ_ONLY_ARB;
    case BufferAccess::Write:
      return GL_WRITE_ONLY_ARB;
    case BufferAccess::ReadWrite:
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
    , helper_(gapi::Extension::extensions)
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

  helper_.BindBuffer(target, getUid().value());
  helper_.BufferData(target, dataSize, data, OGLGenericBuffer::usageToGLenum(usage_));
  helper_.GetBufferParam(target, GL_BUFFER_SIZE_ARB, &allocedSize);

  return allocedSize == dataSize;
}

void OGLGenericBuffer::updateSubdata(u32_t offset, u32_t size, const void *source) {
  auto target = OGLGenericBuffer::targetToGLenum(target_);
  if (helper_.IsBuffer(getUid().value())) {
    helper_.BindBuffer(target, getUid().value());
    helper_.BufferSubData(target, offset, size, source);
    helper_.BindBuffer(target, 0);
  }
}

void OGLGenericBuffer::updateSubdata(const void *source) { updateSubdata(0, capacity_ * byteStride_, source); }

void OGLGenericBuffer::bind() { helper_.BindBuffer(OGLGenericBuffer::targetToGLenum(target_), getUid().value()); }

void OGLGenericBuffer::unbind() { helper_.BindBuffer(OGLGenericBuffer::targetToGLenum(target_), 0); }

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
