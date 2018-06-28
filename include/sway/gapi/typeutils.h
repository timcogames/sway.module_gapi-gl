#ifndef SWAY_GAPI_TYPEUTILS_H
#define SWAY_GAPI_TYPEUTILS_H

#include <sway/gapi/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class TypeUtils {
public:
	static u32_t toGL(u32_t type) {
		switch (type) {
		case kType_Int: return GL_INT;
		case kType_Float: return GL_FLOAT;
		case kType_Double: return GL_DOUBLE;
		case kType_Short: return GL_SHORT;
		case kType_Char: return GL_BYTE;
		/* Поддерживаемые форматы индексов. */
		case kType_UInt: return GL_UNSIGNED_INT;
		case kType_UShort: return GL_UNSIGNED_SHORT;
		case kType_UChar: return GL_UNSIGNED_BYTE;
		default:
			return 0;
		}
	}
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_TYPEUTILS_H
