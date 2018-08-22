#include <sway/gapi/gl/buffer.h>
#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

DLLAPI_EXPORT BufferRef_t createBuffer(const BufferCreateInfo & createInfo) {
	auto instance = boost::make_shared<Buffer>(createInfo.desc);
	if (instance->allocate(createInfo.data)) return instance;
	return nullptr;
}

GLenum Buffer::targetToGLenum(BufferTarget_t target) {
	switch (target) {
	case BufferTarget_t::kArray: return GL_ARRAY_BUFFER_ARB;
	case BufferTarget_t::kElementArray: return GL_ELEMENT_ARRAY_BUFFER_ARB;
	default:
		return 0;
	}
}

GLenum Buffer::usageToGLenum(BufferUsage_t usage) {
	switch (usage) {
	case BufferUsage_t::kStatic: return GL_STATIC_DRAW_ARB;
	case BufferUsage_t::kDynamic: return GL_DYNAMIC_DRAW_ARB;
	case BufferUsage_t::kStream: return GL_STREAM_DRAW_ARB;
	default:
		return 0;
	}
}

GLenum Buffer::accessToGLenum(BufferAccess_t access) {
	switch (access) {
	case BufferAccess_t::kRead: return GL_READ_ONLY_ARB;
	case BufferAccess_t::kWrite: return GL_WRITE_ONLY_ARB;
	case BufferAccess_t::kReadWrite: return GL_READ_WRITE_ARB;
	default:
		return 0;
	}
}

Buffer::Buffer(const BufferDescriptor & desc) : ABufferBase(desc)
	, _allocedSize(0) {
	setTarget(desc.target);
	setUsage(desc.usage);
	setByteStride(desc.byteStride);
	setCapacity(desc.capacity);

	Extension::glGenBuffers(1, &_objectId);
}

Buffer::~Buffer() {
	Extension::glDeleteBuffers(1, &_objectId);
}

bool Buffer::allocate(const void * data) {
	s32_t dataSize = _capacity * _byteStride;

	Extension::glBindBuffer(_target, _objectId);
	Extension::glBufferData(_target, dataSize, data, _usage);

	Extension::glGetBufferParameteriv(_target, GL_BUFFER_SIZE_ARB, &_allocedSize);
	if (_allocedSize != dataSize)
		return false;

	return true;
}

void Buffer::updateSubdata(u32_t offset, u32_t size, const void * source) {
	if (Extension::glIsBuffer(_objectId)) {
		Extension::glBindBuffer(_target, _objectId);
		Extension::glBufferSubData(_target, offset, size, source);
		Extension::glBindBuffer(_target, 0);
	}
}

void Buffer::updateSubdata(const void * source) {
	updateSubdata(0, _capacity * _byteStride, source);
}

void * Buffer::map() {
	Extension::glBindBuffer(_target, _objectId);
	GLvoid * mapped = Extension::glMapBuffer(_target, GL_WRITE_ONLY_ARB);
	if (!mapped)
		return NULL;
	Extension::glBindBuffer(_target, 0);

	return mapped;
}

void Buffer::unmap() {
	Extension::glBindBuffer(_target, _objectId);
	Extension::glUnmapBuffer(_target);
	Extension::glBindBuffer(_target, 0);
}

void Buffer::bind() {
	Extension::glBindBuffer(_target, _objectId);
}

void Buffer::unbind() {
	Extension::glBindBuffer(_target, 0);
}

u32_t Buffer::getAllocedSize() const {
	return _allocedSize;
}

void Buffer::setTarget(BufferTarget_t target) {
	_target = Buffer::targetToGLenum(target);
}

BufferTarget_t Buffer::getTarget() const {
	switch (_target) {
	case GL_ARRAY_BUFFER_ARB: return BufferTarget_t::kArray;
	case GL_ELEMENT_ARRAY_BUFFER_ARB: return BufferTarget_t::kElementArray;
	default:
		return BufferTarget_t::kNone;
	}
}

void Buffer::setUsage(BufferUsage_t usage) {
	_usage = Buffer::usageToGLenum(usage);
}

BufferUsage_t Buffer::getUsage() const {
	switch (_usage) {
	case GL_STATIC_DRAW_ARB: return BufferUsage_t::kStatic;
	case GL_DYNAMIC_DRAW_ARB: return BufferUsage_t::kDynamic;
	case GL_STREAM_DRAW_ARB: return BufferUsage_t::kStream;
	default:
		return BufferUsage_t::kNone;
	}
}

void Buffer::setCapacity(s32_t capacity) {
	_capacity = capacity;
}

s32_t Buffer::getCapacity() const {
	return _capacity;
}

void Buffer::setByteStride(s32_t stride) {
	_byteStride = stride;
}

s32_t Buffer::getByteStride() const {
	return _byteStride;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
