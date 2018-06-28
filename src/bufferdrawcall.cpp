#include "bufferdrawcall.h"
#include "primitivetopology.h"
#include "typeutils.h"

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gl)

GLenum BufferDrawCall::topologyToGLenum(u32_t topology) {
	switch (topology) {
	case kPrimitiveTopology_PointList: return GL_POINTS;
	case kPrimitiveTopology_LineList: return GL_LINES;
	case kPrimitiveTopology_LineStrip: return GL_LINE_STRIP;
	case kPrimitiveTopology_TriangleList: return GL_TRIANGLES;
	case kPrimitiveTopology_TriangleStrip: return GL_TRIANGLE_STRIP;
	case kPrimitiveTopology_TriangleFan: return GL_TRIANGLE_FAN;
	default:
		return 0;
	}
}

BufferDrawCall::BufferDrawCall() {
	// Empty
}

BufferDrawCall::~BufferDrawCall() {
	// Empty
}

void BufferDrawCall::update(u32_t topology, s32_t count, u32_t dataType, bool indexed) {
	if (indexed) {
		_drawCallFunc = boost::bind(&BufferDrawCall::_drawIndexed, this, _1);

		_drawElements.mode = BufferDrawCall::topologyToGLenum(topology);
		_drawElements.count = count;
		_drawElements.type = gl::TypeUtils::toGL(dataType);
	}
	else {
		_drawCallFunc = boost::bind(&BufferDrawCall::_draw, this, _1);

		_drawArrays.mode = BufferDrawCall::topologyToGLenum(topology);
		_drawArrays.first = 0;
		_drawArrays.count = count;
	}
}

void BufferDrawCall::execute(BufferObject * indexBuffer) {
	if (_drawCallFunc)
		_drawCallFunc(indexBuffer);
}

void BufferDrawCall::_draw(BufferObject * indexBuffer) {
	boost::ignore_unused(indexBuffer);
	glDrawArrays(_drawArrays.mode, _drawArrays.first, _drawArrays.count);
}

void BufferDrawCall::_drawIndexed(BufferObject * indexBuffer) {
	BOOST_ASSERT(indexBuffer);

	indexBuffer->bind();
	glDrawElements(_drawElements.mode, _drawElements.count, _drawElements.type, NULL);
	indexBuffer->unbind();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
