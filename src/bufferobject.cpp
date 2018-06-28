#include <sway/gapi/bufferobject.h>
#include <sway/gapi/buffertargets.h>
#include <sway/gapi/bufferusages.h>
#include <sway/gapi/bufferaccesses.h>
#include <sway/gapi/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

GLenum BufferObject::targetToGLenum(u32_t target) {
	switch (target) {
	case kBufferTarget_Array: return GL_ARRAY_BUFFER_ARB;
	case kBufferTarget_ElementArray: return GL_ELEMENT_ARRAY_BUFFER_ARB;
	default:
		return 0;
	}
}

GLenum BufferObject::usageToGLenum(u32_t usage) {
	switch (usage) {
	case kBufferUsage_Static: return GL_STATIC_DRAW_ARB;
	case kBufferUsage_Dynamic: return GL_DYNAMIC_DRAW_ARB;
	case kBufferUsage_Stream: return GL_STREAM_DRAW_ARB;
	default:
		return 0;
	}
}

GLenum BufferObject::accessToGLenum(u32_t access) {
	switch (access) {
	case kBufferAccess_Read: return GL_READ_ONLY_ARB;
	case kBufferAccess_Write: return GL_WRITE_ONLY_ARB;
	case kBufferAccess_ReadWrite: return GL_READ_WRITE_ARB;
	default:
		return 0;
	}
}

BufferObject * BufferObject::create(const BufferCreateInfo & info) {
	BufferObject * instance = new BufferObject(info.description);
	if (instance->allocate(info.data)) return instance;
	SAFE_DELETE(instance);
	return 0;
}

BufferObject::BufferObject(const BufferDescription & desc)
	: _allocedSize(0) {
	setTarget(desc.target);
	setUsage(desc.usage);
	setByteStride(desc.byteStride);
	setCapacity(desc.capacity);
	setDataType(desc.datatype);

	/* Создает аппаратный буфер. */
	Extensions::glGenBuffersARB(1, &_resourceId);
}

BufferObject::~BufferObject() {
	/* Удаляет аппаратный буфер. */
	Extensions::glDeleteBuffersARB(1, &_resourceId);
}

bool BufferObject::allocate(const void * data) {
	s32_t dataSize = _capacity * _byteStride;

	Extensions::glBindBufferARB(_target, _resourceId);
	Extensions::glBufferDataARB(_target, dataSize, data, _usage);

	Extensions::glGetBufferParameterivARB(_target, GL_BUFFER_SIZE_ARB, &_allocedSize);
	if (_allocedSize != dataSize)
		return false;

	return true;
}

void BufferObject::updateSubdata(u32_t offset, u32_t size, const void * source) {
	if (Extensions::glIsBufferARB(_resourceId)) {
		Extensions::glBindBufferARB(_target, _resourceId);
		Extensions::glBufferSubDataARB(_target, offset, size, source);
		Extensions::glBindBufferARB(_target, 0);
	}
}

void BufferObject::updateSubdata(const void * source) {
	updateSubdata(0, _capacity * _byteStride, source);
}

void * BufferObject::map() {
	Extensions::glBindBufferARB(_target, _resourceId);
	GLvoid * mapped = Extensions::glMapBufferARB(_target, GL_WRITE_ONLY_ARB);
	if (!mapped)
		return NULL;
	Extensions::glBindBufferARB(_target, 0);

	return mapped;
}

void BufferObject::unmap() {
	Extensions::glBindBufferARB(_target, _resourceId);
	Extensions::glUnmapBufferARB(_target);
	Extensions::glBindBufferARB(_target, 0);
}

void BufferObject::bind() {
	Extensions::glBindBufferARB(_target, _resourceId);
}

void BufferObject::unbind() {
	Extensions::glBindBufferARB(_target, 0);
}

u32_t BufferObject::getAllocedSize() const {
	return _allocedSize;
}

void BufferObject::setTarget(u32_t target) {
	_target = BufferObject::targetToGLenum(target);
}

u32_t BufferObject::getTarget() const {
	switch (_target) {
	case GL_ARRAY_BUFFER_ARB: return kBufferTarget_Array;
	case GL_ELEMENT_ARRAY_BUFFER_ARB: return kBufferTarget_ElementArray;
	default:
		return 0;
	}
}

void BufferObject::setUsage(u32_t usage) {
	_usage = BufferObject::usageToGLenum(usage);
}

u32_t BufferObject::getUsage() const {
	switch (_usage) {
	case GL_STATIC_DRAW_ARB: return kBufferUsage_Static;
	case GL_DYNAMIC_DRAW_ARB: return kBufferUsage_Dynamic;
	case GL_STREAM_DRAW_ARB: return kBufferUsage_Stream;
	default:
		return 0;
	}
}

void BufferObject::setCapacity(s32_t capacity) {
	_capacity = capacity;
}

s32_t BufferObject::getCapacity() const {
	return _capacity;
}

void BufferObject::setByteStride(s32_t byteStride) {
	_byteStride = byteStride;
}

s32_t BufferObject::getByteStride() const {
	return _byteStride;
}

void BufferObject::setDataType(u32_t type) {
	_datatype = type;
}

u32_t BufferObject::getDataType() const {
	return _datatype;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
