#ifndef SWAY_GAPI_EXTENSIONS_H
#define SWAY_GAPI_EXTENSIONS_H

#include <sway/gapi/extensionsupport.h>
#include <sway/core.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

#define LOAD_EXTENSION(proc, name) \
	name = (proc) glXGetProcAddressARB((const u8_t *) #name);

class Extensions {
public:
	static PFNGLGENBUFFERSARBPROC glGenBuffersARB;
	static PFNGLBINDBUFFERARBPROC glBindBufferARB;
	static PFNGLBUFFERDATAARBPROC glBufferDataARB;
	static PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB;
	static PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
	static PFNGLISBUFFERARBPROC glIsBufferARB;
	static PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
	static PFNGLMAPBUFFERARBPROC glMapBufferARB;
	static PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;
	static PFNGLMAPBUFFERRANGEPROC glMapBufferRange;
	static PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
	static PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
	static PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
	static PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
	static PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
	static PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
	static PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
	static PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB;
	static PFNGLDETACHOBJECTARBPROC glDetachObjectARB;
	static PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
	static PFNGLVALIDATEPROGRAMARBPROC glValidateProgramARB;
	static PFNGLUNIFORM4FARBPROC glUniform4fARB;
	static PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
	static PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
	static PFNGLDELETEPROGRAMSARBPROC glDeleteProgramsARB;
	static PFNGLGETPROGRAMIVARBPROC glGetProgramivARB;
	static PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB;
	static PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;
	static PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB;
	static PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocationARB;
	static PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;

	static bool checkSupport(lpcstr_t extensions, lpcstr_t name);
	static ExtensionSupport define();
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_EXTENSIONS_H
