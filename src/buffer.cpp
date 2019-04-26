#include <sway/gapi/gl/buffer.h>
#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

DLLAPI_EXPORT BufferRef_t createBuffer(const BufferCreateInfo & createInfo) {
	auto instance = std::make_shared<Buffer>(createInfo.desc);
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
	, _target(desc.target)
	, _usage(desc.usage)
	, _byteStride(desc.byteStride)
	, _capacity(desc.capacity) {
	Extension::glGenBuffers(1, &_objectId);
}

Buffer::~Buffer() {
	Extension::glDeleteBuffers(1, &_objectId);
}

bool Buffer::allocate(const void * data) {
	u32_t target = Buffer::targetToGLenum(_target);
	s32_t dataSize = _capacity * _byteStride;
	s32_t allocedSize = 0;

	Extension::glBindBuffer(target, _objectId);
	Extension::glBufferData(target, dataSize, data, Buffer::usageToGLenum(_usage));

	Extension::glGetBufferParameteriv(target, GL_BUFFER_SIZE_ARB, &allocedSize);
	if (allocedSize != dataSize)
		return false;

	return true;
}

void Buffer::updateSubdata(u32_t offset, u32_t size, const void * source) {
	u32_t target = Buffer::targetToGLenum(_target);

	if (Extension::glIsBuffer(_objectId)) {
		Extension::glBindBuffer(target, _objectId);
		Extension::glBufferSubData(target, offset, size, source);
		Extension::glBindBuffer(target, 0);
	}
}

void Buffer::updateSubdata(const void * source) {
	updateSubdata(0, _capacity * _byteStride, source);
}

void * Buffer::map() {
	u32_t target = Buffer::targetToGLenum(_target);

	Extension::glBindBuffer(target, _objectId);
	GLvoid * mapped = Extension::glMapBuffer(target, GL_WRITE_ONLY_ARB);
	if (!mapped)
		return NULL;
	Extension::glBindBuffer(target, 0);

	return mapped;
}

void Buffer::unmap() {
	u32_t target = Buffer::targetToGLenum(_target);

	Extension::glBindBuffer(target, _objectId);
	Extension::glUnmapBuffer(target);
	Extension::glBindBuffer(target, 0);
}

void Buffer::bind() {
	Extension::glBindBuffer(Buffer::targetToGLenum(_target), _objectId);
}

void Buffer::unbind() {
	Extension::glBindBuffer(Buffer::targetToGLenum(_target), 0);
}

BufferTarget_t Buffer::getTarget() const {
	return _target;
}

BufferUsage_t Buffer::getUsage() const {
	return _usage;
}

s32_t Buffer::getCapacity() const {
	return _capacity;
}

s32_t Buffer::getByteStride() const {
	return _byteStride;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
