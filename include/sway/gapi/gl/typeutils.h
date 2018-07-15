#ifndef SWAY_GAPI_GL_TYPEUTILS_H
#define SWAY_GAPI_GL_TYPEUTILS_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class TypeUtils {
public:
	static u32_t toGL(Type_t type) {
		switch (type) {
		case Type_t::kChar: return GL_BYTE;
		case Type_t::kShort: return GL_SHORT;
		case Type_t::kInt: return GL_INT;
		case Type_t::kUChar: return GL_UNSIGNED_BYTE;
		case Type_t::kUShort: return GL_UNSIGNED_SHORT;
		case Type_t::kUInt: return GL_UNSIGNED_INT;
		case Type_t::kFloat: return GL_FLOAT;
		case Type_t::kDouble: return GL_DOUBLE;
		default:
			return 0;
		}
	}
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_TYPEUTILS_H
