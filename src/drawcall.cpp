#include <sway/gapi/gl/drawcall.h>
#include <sway/gapi/gl/extensions.h>
#include <sway/gapi/gl/typeutils.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

GLenum DrawCall::topologyToGLenum(PrimitiveType_t topology) {
	switch (topology) {
	case PrimitiveType_t::kPointList: return GL_POINTS;
	case PrimitiveType_t::kLineList: return GL_LINES;
	case PrimitiveType_t::kLineStrip: return GL_LINE_STRIP;
	case PrimitiveType_t::kTriangleList: return GL_TRIANGLES;
	case PrimitiveType_t::kTriangleStrip: return GL_TRIANGLE_STRIP;
	case PrimitiveType_t::kTriangleFan: return GL_TRIANGLE_FAN;
	default:
		return 0;
	}
}

void DrawCall::execute(PrimitiveType_t topology, s32_t count, IBufferBase * ibo, Type_t type) {
	if (ibo) {
		_drawCallFunc = boost::bind(&DrawCall::_drawIndexed, this, _1);
		_drawElements.mode = DrawCall::topologyToGLenum(topology);
		_drawElements.count = count;
		_drawElements.type = TypeUtils::toGL(type);
	}
	else {
		_drawCallFunc = boost::bind(&DrawCall::_draw, this, _1);
		_drawArrays.mode = DrawCall::topologyToGLenum(topology);
		_drawArrays.first = 0;
		_drawArrays.count = count;
	}

	if (_drawCallFunc)
		_drawCallFunc(static_cast<BufferObject *>(ibo));
}

void DrawCall::_draw(BufferObject * ibo) {
	boost::ignore_unused(ibo);
	glDrawArrays(_drawArrays.mode, _drawArrays.first, _drawArrays.count);
}

void DrawCall::_drawIndexed(BufferObject * ibo) {
	if (Extensions::glIsBufferARB(ibo->getObjectId())) {
		// Empty
	}

	ibo->bind();
	glDrawElements(_drawElements.mode, _drawElements.count, _drawElements.type, NULL);
	ibo->unbind();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
