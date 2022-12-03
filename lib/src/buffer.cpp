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
    case BufferTarget_t::kArray:
      return GL_ARRAY_BUFFER;
    case BufferTarget_t::kElementArray:
      return GL_ELEMENT_ARRAY_BUFFER;
    default:
      return 0;
  }
#else
  switch (target) {
    case BufferTarget_t::kArray:
      return GL_ARRAY_BUFFER_ARB;
    case BufferTarget_t::kElementArray:
      return GL_ELEMENT_ARRAY_BUFFER_ARB;
    default:
      return 0;
  }
#endif
}

auto Buffer::usageToGLenum(BufferUsage_t usage) -> GLenum {
#ifdef _EMSCRIPTEN
  switch (usage) {
    case BufferUsage_t::kStatic:
      return GL_STATIC_DRAW;
    case BufferUsage_t::kDynamic:
      return GL_DYNAMIC_DRAW;
    case BufferUsage_t::kStream:
      return GL_STREAM_DRAW;
    default:
      return 0;
  }
#else
  switch (usage) {
    case BufferUsage_t::kStatic:
      return GL_STATIC_DRAW_ARB;
    case BufferUsage_t::kDynamic:
      return GL_DYNAMIC_DRAW_ARB;
    case BufferUsage_t::kStream:
      return GL_STREAM_DRAW_ARB;
    default:
      return 0;
  }
#endif
}

auto Buffer::accessToGLenum(BufferAccess_t access) -> GLenum {
#ifdef _EMSCRIPTEN
  switch (access) {
    case BufferAccess_t::kRead:
      return GL_READ_ONLY;
    case BufferAccess_t::kWrite:
      return GL_WRITE_ONLY;
    case BufferAccess_t::kReadWrite:
      return GL_READ_WRITE;
    default:
      return 0;
  }
#else
  switch (access) {
    case BufferAccess_t::kRead:
      return GL_READ_ONLY_ARB;
    case BufferAccess_t::kWrite:
      return GL_WRITE_ONLY_ARB;
    case BufferAccess_t::kReadWrite:
      return GL_READ_WRITE_ARB;
    default:
      return 0;
  }
#endif
}

auto Buffer::createInstance(const BufferCreateInfo &createInfo) -> BufferRef_t {
  auto instance = std::make_shared<Buffer>(createInfo.desc);
  if (instance->allocate(createInfo.data)) {
    return instance;
  }

  return nullptr;
}

Buffer::Buffer(const BufferDescriptor &desc)
    : ABufferBase(desc)
    , target_(desc.target)
    , usage_(desc.usage)
    , capacity_(desc.capacity)
    , byteStride_(desc.byteStride) {
#ifdef _EMSCRIPTEN
  glGenBuffers(1, &_objectId);
#else
  Extension::glGenBuffers(1, &_objectId);
#endif
}

Buffer::~Buffer() {
#ifdef _EMSCRIPTEN
  glDeleteBuffers(1, &_objectId);
#else
  Extension::glDeleteBuffers(1, &_objectId);
#endif
}

auto Buffer::allocate(const void *data) -> bool {
  u32_t target = Buffer::targetToGLenum(target_);
  s32_t dataSize = capacity_ * byteStride_;
  s32_t allocedSize = 0;

#ifdef _EMSCRIPTEN
  glBindBuffer(target, _objectId);
  glBufferData(target, dataSize, data, Buffer::usageToGLenum(usage_));

  glGetBufferParameteriv(target, GL_BUFFER_SIZE_ARB, &allocedSize);
#else
  Extension::glBindBuffer(target, _objectId);
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
  if (glIsBuffer(_objectId)) {
    glBindBuffer(target, _objectId);
    glBufferSubData(target, offset, size, source);
    glBindBuffer(target, 0);
  }
#else
  if (Extension::glIsBuffer(_objectId)) {
    Extension::glBindBuffer(target, _objectId);
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
  // glBindBuffer(target, _objectId);
  // mapped = glMapBuffer(target, GL_WRITE_ONLY);
  // if (!mapped) {
  //   return nullptr;
  // }

  // glBindBuffer(target, 0);
#else
  Extension::glBindBuffer(target, _objectId);
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
  // glBindBuffer(target, _objectId);
  // glUnmapBufferOES(target);
  // glBindBuffer(target, 0);
#else
  Extension::glBindBuffer(target, _objectId);
  Extension::glUnmapBuffer(target);
  Extension::glBindBuffer(target, 0);
#endif
}

void Buffer::bind() {
#ifdef _EMSCRIPTEN
  glBindBuffer(Buffer::targetToGLenum(target_), _objectId);
#else
  Extension::glBindBuffer(Buffer::targetToGLenum(target_), _objectId);
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
