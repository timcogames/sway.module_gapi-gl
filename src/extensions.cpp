#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

PFNGLGENBUFFERSARBPROC Extensions::glGenBuffersARB = NULL;
PFNGLBINDBUFFERARBPROC Extensions::glBindBufferARB = NULL;
PFNGLBUFFERDATAARBPROC Extensions::glBufferDataARB = NULL;
PFNGLGETBUFFERPARAMETERIVARBPROC Extensions::glGetBufferParameterivARB = NULL;
PFNGLDELETEBUFFERSARBPROC Extensions::glDeleteBuffersARB = NULL;
PFNGLISBUFFERARBPROC Extensions::glIsBufferARB = NULL;
PFNGLBUFFERSUBDATAARBPROC Extensions::glBufferSubDataARB = NULL;
PFNGLMAPBUFFERARBPROC Extensions::glMapBufferARB = NULL;
PFNGLUNMAPBUFFERARBPROC Extensions::glUnmapBufferARB = NULL;
PFNGLMAPBUFFERRANGEPROC Extensions::glMapBufferRange = NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC Extensions::glCreateProgramObjectARB = NULL;
PFNGLCREATESHADEROBJECTARBPROC Extensions::glCreateShaderObjectARB = NULL;
PFNGLSHADERSOURCEARBPROC Extensions::glShaderSourceARB = NULL;
PFNGLCOMPILESHADERARBPROC Extensions::glCompileShaderARB = NULL;
PFNGLATTACHOBJECTARBPROC Extensions::glAttachObjectARB = NULL;
PFNGLLINKPROGRAMARBPROC Extensions::glLinkProgramARB = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC Extensions::glUseProgramObjectARB = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC Extensions::glGetUniformLocationARB = NULL;
PFNGLDETACHOBJECTARBPROC Extensions::glDetachObjectARB = NULL;
PFNGLDELETEOBJECTARBPROC Extensions::glDeleteObjectARB = NULL;
PFNGLVALIDATEPROGRAMARBPROC Extensions::glValidateProgramARB = NULL;
PFNGLUNIFORM4FARBPROC Extensions::glUniform4fARB = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC Extensions::glGetObjectParameterivARB = NULL;
PFNGLGETINFOLOGARBPROC Extensions::glGetInfoLogARB = NULL;
PFNGLDELETEPROGRAMSARBPROC Extensions::glDeleteProgramsARB = NULL;
PFNGLGETPROGRAMIVARBPROC Extensions::glGetProgramivARB = NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC Extensions::glEnableVertexAttribArrayARB = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC Extensions::glDisableVertexAttribArrayARB = NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC Extensions::glVertexAttribPointerARB = NULL;
PFNGLGETATTRIBLOCATIONARBPROC Extensions::glGetAttribLocationARB = NULL;
PFNGLACTIVETEXTUREARBPROC Extensions::glActiveTextureARB = NULL;

bool Extensions::checkSupport(lpcstr_t extensions, lpcstr_t name) {
	if (!strstr(extensions, name)) {
		printf("Extension %s is not supported.\n", name);
		return false;
	}

	return true;
}

ExtensionSupport Extensions::define() {
	ExtensionSupport support;
	lpcstr_t extensions = (lpcstr_t) glGetString(GL_EXTENSIONS);

	support.arb.vertexBufferObject = checkSupport(extensions, "GL_ARB_vertex_buffer_object");
	if (support.arb.vertexBufferObject) {
		LOAD_EXTENSION(PFNGLGENBUFFERSARBPROC, glGenBuffersARB);
		LOAD_EXTENSION(PFNGLBINDBUFFERARBPROC, glBindBufferARB);
		LOAD_EXTENSION(PFNGLBUFFERDATAARBPROC, glBufferDataARB);
		LOAD_EXTENSION(PFNGLGETBUFFERPARAMETERIVARBPROC, glGetBufferParameterivARB);
		LOAD_EXTENSION(PFNGLDELETEBUFFERSARBPROC, glDeleteBuffersARB);
		LOAD_EXTENSION(PFNGLISBUFFERARBPROC, glIsBufferARB);
		LOAD_EXTENSION(PFNGLBUFFERSUBDATAARBPROC, glBufferSubDataARB);
		LOAD_EXTENSION(PFNGLMAPBUFFERARBPROC, glMapBufferARB);
		LOAD_EXTENSION(PFNGLUNMAPBUFFERARBPROC, glUnmapBufferARB);
	}

	support.arb.mapBufferRange = checkSupport(extensions, "GL_ARB_map_buffer_range");
	if (support.arb.mapBufferRange) {
		LOAD_EXTENSION(PFNGLMAPBUFFERRANGEPROC, glMapBufferRange);
	}

	support.arb.shaderObjects = checkSupport(extensions, "GL_ARB_shader_objects");
	if (support.arb.shaderObjects) {
		LOAD_EXTENSION(PFNGLCREATEPROGRAMOBJECTARBPROC, glCreateProgramObjectARB);
		LOAD_EXTENSION(PFNGLCREATESHADEROBJECTARBPROC, glCreateShaderObjectARB);
		LOAD_EXTENSION(PFNGLSHADERSOURCEARBPROC, glShaderSourceARB);
		LOAD_EXTENSION(PFNGLCOMPILESHADERARBPROC, glCompileShaderARB);
		LOAD_EXTENSION(PFNGLATTACHOBJECTARBPROC, glAttachObjectARB);
		LOAD_EXTENSION(PFNGLLINKPROGRAMARBPROC, glLinkProgramARB);
		LOAD_EXTENSION(PFNGLUSEPROGRAMOBJECTARBPROC, glUseProgramObjectARB);
		LOAD_EXTENSION(PFNGLGETUNIFORMLOCATIONARBPROC, glGetUniformLocationARB);
		LOAD_EXTENSION(PFNGLDETACHOBJECTARBPROC, glDetachObjectARB);
		LOAD_EXTENSION(PFNGLDELETEOBJECTARBPROC, glDeleteObjectARB);
		LOAD_EXTENSION(PFNGLVALIDATEPROGRAMARBPROC, glValidateProgramARB);
		LOAD_EXTENSION(PFNGLUNIFORM4FARBPROC, glUniform4fARB);
		LOAD_EXTENSION(PFNGLGETOBJECTPARAMETERIVARBPROC, glGetObjectParameterivARB);
		LOAD_EXTENSION(PFNGLGETINFOLOGARBPROC, glGetInfoLogARB);
	}

	support.arb.fragmentProgram = checkSupport(extensions, "GL_ARB_fragment_program");
	if (support.arb.fragmentProgram) {
		LOAD_EXTENSION(PFNGLDELETEPROGRAMSARBPROC, glDeleteProgramsARB);
		LOAD_EXTENSION(PFNGLGETPROGRAMIVARBPROC, glGetProgramivARB);
	}

	support.arb.vertexProgram = checkSupport(extensions, "GL_ARB_vertex_program");
	if (support.arb.vertexProgram) {
		LOAD_EXTENSION(PFNGLENABLEVERTEXATTRIBARRAYARBPROC, glEnableVertexAttribArrayARB);
		LOAD_EXTENSION(PFNGLDISABLEVERTEXATTRIBARRAYARBPROC, glDisableVertexAttribArrayARB);
		LOAD_EXTENSION(PFNGLVERTEXATTRIBPOINTERARBPROC, glVertexAttribPointerARB);
	}

	support.arb.vertexShader = checkSupport(extensions, "GL_ARB_vertex_shader");
	if (support.arb.vertexShader) {
		LOAD_EXTENSION(PFNGLGETATTRIBLOCATIONARBPROC, glGetAttribLocationARB);
	}

	support.arb.multitexture = checkSupport(extensions, "GL_ARB_multitexture");
	if (support.arb.multitexture) {
		LOAD_EXTENSION(PFNGLACTIVETEXTUREARBPROC, glActiveTextureARB);
	}

	return support;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
