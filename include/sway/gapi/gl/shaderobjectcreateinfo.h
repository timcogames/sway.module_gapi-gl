#ifndef SWAY_GAPI_GL_SHADEROBJECTCREATEINFO_H
#define SWAY_GAPI_GL_SHADEROBJECTCREATEINFO_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct ShaderObjectCreateInfo {
	u32_t type; /*< Тип шейдера. */
	std::string source; /*!< Исходный код шейдера. */
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_SHADEROBJECTCREATEINFO_H
