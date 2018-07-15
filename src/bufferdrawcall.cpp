#include <sway/gapi/gl/bufferdrawcall.h>
#include <sway/gapi/gl/primitivetopologies.h>
#include <sway/gapi/gl/typeutils.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

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

void BufferDrawCall::update(u32_t topology, s32_t count, Type_t type, bool indexed) {
	if (indexed) {
		_drawCallFunc = boost::bind(&BufferDrawCall::_drawIndexed, this, _1);

		_drawElements.mode = BufferDrawCall::topologyToGLenum(topology);
		_drawElements.count = count;
		_drawElements.type = TypeUtils::toGL(type);
	}
	else {
		_drawCallFunc = boost::bind(&BufferDrawCall::_draw, this, _1);

		_drawArrays.mode = BufferDrawCall::topologyToGLenum(topology);
		_drawArrays.first = 0;
		_drawArrays.count = count;
	}
}

void BufferDrawCall::execute(BufferObject * ibo) {
	if (_drawCallFunc)
		_drawCallFunc(ibo);
}

void BufferDrawCall::_draw(BufferObject * ibo) {
	boost::ignore_unused(ibo);
	glDrawArrays(_drawArrays.mode, _drawArrays.first, _drawArrays.count);
}

void BufferDrawCall::_drawIndexed(BufferObject * ibo) {
	BOOST_ASSERT(ibo);

	ibo->bind();
	glDrawElements(_drawElements.mode, _drawElements.count, _drawElements.type, NULL);
	ibo->unbind();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
