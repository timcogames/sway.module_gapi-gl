#ifndef SWAY_GAPI_GL_EXTENSIONSUPPORT_H
#define SWAY_GAPI_GL_EXTENSIONSUPPORT_H

#include <sway/core.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct ExtensionSupport {
	struct {
		bool bVertexBufferObject;
		bool bMapBufferRange;
		bool bShaderObjects;
		bool bFragmentProgram;
		bool bVertexProgram;
		bool bVertexShader;
		bool bMultitexture;
	} arb;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_EXTENSIONSUPPORT_H
