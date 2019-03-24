#ifndef SWAY_GAPI_GL_TYPEUTILS_H
#define SWAY_GAPI_GL_TYPEUTILS_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class TypeUtils {
public:
	static u32_t toGL(core::detail::DataType_t type) {
		switch (type) {
		case core::detail::DataType_t::kChar: return GL_BYTE;
		case core::detail::DataType_t::kShort: return GL_SHORT;
		case core::detail::DataType_t::kInt: return GL_INT;
		case core::detail::DataType_t::kUChar: return GL_UNSIGNED_BYTE;
		case core::detail::DataType_t::kUShort: return GL_UNSIGNED_SHORT;
		case core::detail::DataType_t::kUInt: return GL_UNSIGNED_INT;
		case core::detail::DataType_t::kFloat: return GL_FLOAT;
		case core::detail::DataType_t::kDouble: return GL_DOUBLE;
		default:
			return 0;
		}
	}
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_TYPEUTILS_H
