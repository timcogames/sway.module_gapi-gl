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
	kPrimitiveTopology_PointList     = 0xFE12,
	kPrimitiveTopology_LineList      = 0xFDBE,
	kPrimitiveTopology_LineStrip     = 0x6B83,
	kPrimitiveTopology_TriangleList  = 0x7DD0, /*!< Список треугольников. */
	kPrimitiveTopology_TriangleStrip = 0x9FAE,
	kPrimitiveTopology_TriangleFan   = 0x3EAC
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_PRIMITIVETOPOLOGIES_H
