#include <sway/gapi/gl/drawcall.h>
#include <sway/gapi/gl/buffer.h>
#include <sway/gapi/gl/extensions.h>
#include <sway/gapi/gl/typeutils.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

GLenum DrawCall::topologyToGLenum(TopologyType_t topology) {
	switch (topology) {
	case TopologyType_t::kPointList: return GL_POINTS;
	case TopologyType_t::kLineList: return GL_LINES;
	case TopologyType_t::kLineStrip: return GL_LINE_STRIP;
	case TopologyType_t::kTriangleList: return GL_TRIANGLES;
	case TopologyType_t::kTriangleStrip: return GL_TRIANGLE_STRIP;
	case TopologyType_t::kTriangleFan: return GL_TRIANGLE_FAN;
	default:
		return 0;
	}
}

DrawCallRef_t DrawCall::createInstance() {
	auto instance = std::make_shared<DrawCall>();
	return instance;
}

void DrawCall::execute(TopologyType_t topology, BufferSet bufset, core::detail::DataType_t type) {
	if (bufset.ibo) {
		_drawCbFunc = boost::bind(&DrawCall::_drawIndexed, this, _1);
		_drawElements.mode = DrawCall::topologyToGLenum(topology);
		_drawElements.count = bufset.ibo->getCapacity();
		_drawElements.type = TypeUtils::toGL(type);
	}
	else {
		_drawCbFunc = boost::bind(&DrawCall::_draw, this, _1);
		_drawArrays.mode = DrawCall::topologyToGLenum(topology);
		_drawArrays.first = 0;
		_drawArrays.count = bufset.vbo->getCapacity();
	}

	if (_drawCbFunc)
		_drawCbFunc(bufset.ibo);
}

void DrawCall::_draw(BufferRef_t ibo) {
	boost::ignore_unused(ibo);
	glDrawArrays(_drawArrays.mode, _drawArrays.first, _drawArrays.count);
}

void DrawCall::_drawIndexed(BufferRef_t ibo) {
	if (Extension::glIsBuffer(ibo->getObjectId())) {
		// Empty
	}

	ibo->bind();
	glDrawElements(_drawElements.mode, _drawElements.count, _drawElements.type, nullptr);
	ibo->unbind();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
