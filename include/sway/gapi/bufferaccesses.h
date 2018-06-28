#ifndef SWAY_GAPI_BUFFERACCESSES_H
#define SWAY_GAPI_BUFFERACCESSES_H

#include <sway/gapi/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

enum BufferAccesses {
	kBufferAccess_Read,
	kBufferAccess_Write,
	kBufferAccess_ReadWrite
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_BUFFERACCESSES_H
