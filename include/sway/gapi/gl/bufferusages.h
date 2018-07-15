#ifndef SWAY_GAPI_GL_BUFFERUSAGES_H
#define SWAY_GAPI_GL_BUFFERUSAGES_H

#include <sway/namespacemacros.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

enum BufferUsages {
	kBufferUsage_None,
	kBufferUsage_Static,
	kBufferUsage_Dynamic,
	kBufferUsage_Stream
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_BUFFERUSAGES_H
