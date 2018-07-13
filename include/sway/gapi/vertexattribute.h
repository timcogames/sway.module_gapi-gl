#ifndef SWAY_GAPI_VERTEXATTRIBUTE_H
#define SWAY_GAPI_VERTEXATTRIBUTE_H

#include <sway/gapi/vertexsemantics.h>
#include <sway/gapi/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct VertexAttribute {
	s32_t location;
	VertexSemantic_t semantic;
	Type_t format; /*!< Формат данных. */
	s32_t numComponents; /*!< Количество компонентов. */
	s32_t stride;
	const void * offset;
	bool normalized; /*!< Нормализация входных данных. */
	bool enabled;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_VERTEXATTRIBUTE_H
