#include <sway/gapi/gl/buffer.hpp>
#include <sway/gapi/gl/extensions.hpp>

// #define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

// SWAY_USE_EMSCRIPTEN

auto Buffer::targetToGLenum(BufferTarget_t target) -> GLenum {
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

auto Buffer::usageToGLenum(BufferUsage_t usage) -> GLenum {
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

auto Buffer::accessToGLenum(BufferAccess_t access) -> GLenum {
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

auto Buffer::createInstance(BufferIdQueueRef_t idQueue, const BufferCreateInfo &createInfo) -> BufferRef_t {
  auto instance = std::make_shared<Buffer>(idQueue, createInfo.desc);
  if (instance->allocate(createInfo.data)) {
    return instance;
  }

  return nullptr;
}

#define INVALID_BUFFER_OBJECT_NAME (-1)
using BufferObjectIdType = u32_t;

Buffer::Buffer(BufferIdQueueRef_t idQueue, const BufferDescriptor &desc)
    : BufferBase(desc)
    , target_(desc.target)
    , usage_(desc.usage)
    , capacity_(desc.capacity)
    , byteStride_(desc.byteStride) {
  setUid(idQueue->getBufferId());
}

Buffer::~Buffer() {
  auto objectId = getUid().value();
#ifdef _EMSCRIPTEN
  glDeleteBuffers(1, &objectId);
#else
  Extension::glDeleteBuffers(1, &objectId);
#endif
}

auto Buffer::allocate(const void *data) -> bool {
  u32_t target = Buffer::targetToGLenum(target_);
  s32_t dataSize = capacity_ * byteStride_;
  s32_t allocedSize = 0;

#ifdef _EMSCRIPTEN
  glBindBuffer(target, getUid().value());
  glBufferData(target, dataSize, data, Buffer::usageToGLenum(usage_));

  glGetBufferParameteriv(target, GL_BUFFER_SIZE_ARB, &allocedSize);
#else
  Extension::glBindBuffer(target, getUid().value());
  Extension::glBufferData(target, dataSize, data, Buffer::usageToGLenum(usage_));

  Extension::glGetBufferParameteriv(target, GL_BUFFER_SIZE_ARB, &allocedSize);
#endif

  if (allocedSize != dataSize) {
    return false;
  }

  return true;
}

void Buffer::updateSubdata(u32_t offset, u32_t size, const void *source) {
  u32_t target = Buffer::targetToGLenum(target_);

#ifdef _EMSCRIPTEN
  if (glIsBuffer(getUid().value())) {
    glBindBuffer(target, getUid().value());
    glBufferSubData(target, offset, size, source);
    glBindBuffer(target, 0);
  }
#else
  if (Extension::glIsBuffer(getUid().value())) {
    Extension::glBindBuffer(target, getUid().value());
    Extension::glBufferSubData(target, offset, size, source);
    Extension::glBindBuffer(target, 0);
  }
#endif
}

void Buffer::updateSubdata(const void *source) { updateSubdata(0, capacity_ * byteStride_, source); }

auto Buffer::map() -> void * {
  GLvoid *mapped = nullptr;
  [[maybe_unused]] u32_t target = Buffer::targetToGLenum(target_);

#ifdef _EMSCRIPTEN
  // glBindBuffer(target, objectId_);
  // mapped = glMapBuffer(target, GL_WRITE_ONLY);
  // if (!mapped) {
  //   return nullptr;
  // }

  // glBindBuffer(target, 0);
#else
  Extension::glBindBuffer(target, getUid().value());
  mapped = Extension::glMapBuffer(target, GL_WRITE_ONLY_ARB);
  if (!mapped) {
    return nullptr;
  }

  Extension::glBindBuffer(target, 0);
#endif

  return mapped;
}

void Buffer::unmap() {
  [[maybe_unused]] u32_t target = Buffer::targetToGLenum(target_);

#ifdef _EMSCRIPTEN
  // glBindBuffer(target, getUid().value());
  // glUnmapBufferOES(target);
  // glBindBuffer(target, 0);
#else
  Extension::glBindBuffer(target, getUid().value());
  Extension::glUnmapBuffer(target);
  Extension::glBindBuffer(target, 0);
#endif
}

void Buffer::bind() {
#ifdef _EMSCRIPTEN
  glBindBuffer(Buffer::targetToGLenum(target_), getUid().value());
#else
  Extension::glBindBuffer(Buffer::targetToGLenum(target_), getUid().value());
#endif
}

void Buffer::unbind() {
#ifdef _EMSCRIPTEN
  glBindBuffer(Buffer::targetToGLenum(target_), 0);
#else
  Extension::glBindBuffer(Buffer::targetToGLenum(target_), 0);
#endif
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
