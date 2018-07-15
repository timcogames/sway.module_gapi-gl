#ifndef SWAY_GAPI_GL_SHADERTYPES_H
#define SWAY_GAPI_GL_SHADERTYPES_H

#include <sway/namespacemacros.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/*!
 * \brief
 *    Перечисление типов шейдера.
 */
enum ShaderTypes {
	kShaderType_Vertex = 0x8B31, /*!< Вершинный шейдер. */
	kShaderType_Fragment = 0x8B30 /*!< Фрагментный шейдер. */
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_SHADERTYPES_H
