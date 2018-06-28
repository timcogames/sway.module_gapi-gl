#ifndef SWAY_GAPI_BUFFERTARGETS_H
#define SWAY_GAPI_BUFFERTARGETS_H

#include <sway/gapi/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

enum BufferTargets {
	kBufferTarget_Array        = 0x2CA1,
	kBufferTarget_ElementArray = 0xE70D,
	kBufferTarget_Uniform      = 0x6986,
	kBufferTarget_Texture      = 0xC14B
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_BUFFERTARGETS_H
