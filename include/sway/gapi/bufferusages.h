#ifndef SWAY_GAPI_BUFFERUSAGES_H
#define SWAY_GAPI_BUFFERUSAGES_H

#include <sway/gapi/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

enum BufferUsages {
	kBufferUsage_Static  = 0xA0E7,
	kBufferUsage_Dynamic = 0xF1D8,
	kBufferUsage_Stream  = 0x7F94
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_BUFFERUSAGES_H
