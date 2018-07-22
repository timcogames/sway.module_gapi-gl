#include <sway/gapi/gl/bufferobject.h>
#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

GLenum BufferObject::targetToGLenum(BufferTarget_t target) {
	switch (target) {
	case BufferTarget_t::kArray: return GL_ARRAY_BUFFER_ARB;
	case BufferTarget_t::kElementArray: return GL_ELEMENT_ARRAY_BUFFER_ARB;
	default:
		return 0;
	}
}

GLenum BufferObject::usageToGLenum(BufferUsage_t usage) {
	switch (usage) {
	case BufferUsage_t::kStatic: return GL_STATIC_DRAW_ARB;
	case BufferUsage_t::kDynamic: return GL_DYNAMIC_DRAW_ARB;
	case BufferUsage_t::kStream: return GL_STREAM_DRAW_ARB;
	default:
		return 0;
	}
}

GLenum BufferObject::accessToGLenum(BufferAccess_t access) {
	switch (access) {
	case BufferAccess_t::kRead: return GL_READ_ONLY_ARB;
	case BufferAccess_t::kWrite: return GL_WRITE_ONLY_ARB;
	case BufferAccess_t::kReadWrite: return GL_READ_WRITE_ARB;
	default:
		return 0;
	}
}

IBufferBase * BufferObject::create(const BufferCreateInfo & info) {
	auto instance = new BufferObject(info.desc);
	if (instance->allocate(info.data)) return instance;
	return 0;
}

BufferObject::BufferObject(const BufferDescriptor & desc) : IBufferBase(desc)
	, _allocedSize(0) {
	setTarget(desc.target);
	setUsage(desc.usage);
	setByteStride(desc.byteStride);
	setCapacity(desc.capacity);

	/* Создает аппаратный буфер. */
	Extensions::glGenBuffersARB(1, &_objectId);
}

BufferObject::~BufferObject() {
	/* Удаляет аппаратный буфер. */
	Extensions::glDeleteBuffersARB(1, &_objectId);
}

bool BufferObject::allocate(const void * data) {
	s32_t dataSize = _capacity * _byteStride;

	Extensions::glBindBufferARB(_target, _objectId);
	Extensions::glBufferDataARB(_target, dataSize, data, _usage);

	Extensions::glGetBufferParameterivARB(_target, GL_BUFFER_SIZE_ARB, &_allocedSize);
	if (_allocedSize != dataSize)
		return false;

	return true;
}

void BufferObject::updateSubdata(u32_t offset, u32_t size, const void * source) {
	if (Extensions::glIsBufferARB(_objectId)) {
		Extensions::glBindBufferARB(_target, _objectId);
		Extensions::glBufferSubDataARB(_target, offset, size, source);
		Extensions::glBindBufferARB(_target, 0);
	}
}

void BufferObject::updateSubdata(const void * source) {
	updateSubdata(0, _capacity * _byteStride, source);
}

void * BufferObject::map() {
	Extensions::glBindBufferARB(_target, _objectId);
	GLvoid * mapped = Extensions::glMapBufferARB(_target, GL_WRITE_ONLY_ARB);
	if (!mapped)
		return NULL;
	Extensions::glBindBufferARB(_target, 0);

	return mapped;
}

void BufferObject::unmap() {
	Extensions::glBindBufferARB(_target, _objectId);
	Extensions::glUnmapBufferARB(_target);
	Extensions::glBindBufferARB(_target, 0);
}

void BufferObject::bind() {
	Extensions::glBindBufferARB(_target, _objectId);
}

void BufferObject::unbind() {
	Extensions::glBindBufferARB(_target, 0);
}

u32_t BufferObject::getAllocedSize() const {
	return _allocedSize;
}

void BufferObject::setTarget(BufferTarget_t target) {
	_target = BufferObject::targetToGLenum(target);
}

BufferTarget_t BufferObject::getTarget() const {
	switch (_target) {
	case GL_ARRAY_BUFFER_ARB: return BufferTarget_t::kArray;
	case GL_ELEMENT_ARRAY_BUFFER_ARB: return BufferTarget_t::kElementArray;
	default:
		return BufferTarget_t::kNone;
	}
}

void BufferObject::setUsage(BufferUsage_t usage) {
	_usage = BufferObject::usageToGLenum(usage);
}

BufferUsage_t BufferObject::getUsage() const {
	switch (_usage) {
	case GL_STATIC_DRAW_ARB: return BufferUsage_t::kStatic;
	case GL_DYNAMIC_DRAW_ARB: return BufferUsage_t::kDynamic;
	case GL_STREAM_DRAW_ARB: return BufferUsage_t::kStream;
	default:
		return BufferUsage_t::kNone;
	}
}

void BufferObject::setCapacity(s32_t capacity) {
	_capacity = capacity;
}

s32_t BufferObject::getCapacity() const {
	return _capacity;
}

void BufferObject::setByteStride(s32_t stride) {
	_byteStride = stride;
}

s32_t BufferObject::getByteStride() const {
	return _byteStride;
}

u32_t BufferObject::getObjectId() const {
	return _objectId;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
