#ifndef SWAY_GAPI_GL_BUFFERDESCRIPTION_H
#define SWAY_GAPI_GL_BUFFERDESCRIPTION_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct BufferDescription {
	u32_t target;
	u32_t usage;
	s32_t byteStride;
	s32_t capacity; /*!< Количество элементов в массиве. */
	u32_t datatype; /*!< Тип данных. */
};

struct BufferCreateInfo {
	BufferDescription description;
	const void * data; /*!< Первоначальный данные. */
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_BUFFERDESCRIPTION_H
