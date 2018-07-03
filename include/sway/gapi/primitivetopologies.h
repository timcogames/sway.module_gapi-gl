#ifndef SWAY_GAPI_PRIMITIVETOPOLOGIES_H
#define SWAY_GAPI_PRIMITIVETOPOLOGIES_H

#include <sway/core.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/*!
 * \brief
 *    Перечисление базовых топологий примитивов (или типов примитивов).
 */
enum PrimitiveTopologies {
	kPrimitiveTopology_None,
	kPrimitiveTopology_PointList,
	kPrimitiveTopology_LineList,
	kPrimitiveTopology_LineStrip,
	kPrimitiveTopology_TriangleList, /*!< Список треугольников. */
	kPrimitiveTopology_TriangleStrip,
	kPrimitiveTopology_TriangleFan
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_PRIMITIVETOPOLOGIES_H
