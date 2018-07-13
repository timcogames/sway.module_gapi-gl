#ifndef SWAY_GAPI_BUFFERTARGETS_H
#define SWAY_GAPI_BUFFERTARGETS_H

#include <sway/namespacemacros.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

enum BufferTargets {
	kBufferTarget_None,
	kBufferTarget_Array,
	kBufferTarget_ElementArray,
	kBufferTarget_Uniform,
	kBufferTarget_Texture
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_BUFFERTARGETS_H
