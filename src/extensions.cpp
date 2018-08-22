#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

core::binding::TFunction<u32_t ()> Extension::glCreateProgramObject = NULL;
core::binding::TFunction<void (s32_t num, const u32_t * programs)> Extension::glDeletePrograms = NULL;
core::binding::TFunction<void (u32_t containerObj, u32_t obj)> Extension::glAttachObject = NULL;
core::binding::TFunction<void (u32_t containerObj, u32_t attachedObj)> Extension::glDetachObject = NULL;
core::binding::TFunction<void (u32_t programObj)> Extension::glLinkProgram = NULL;
core::binding::TFunction<void (u32_t programObj)> Extension::glValidateProgram = NULL;
core::binding::TFunction<void (u32_t programObj)> Extension::glUseProgramObject = NULL;
core::binding::TFunction<s32_t (u32_t programObj, lpcstr_t name)> Extension::glGetUniformLocation = NULL;
core::binding::TFunction<void (s32_t location, f32_t v0, f32_t v1, f32_t v2, f32_t v3)> Extension::glUniform4f = NULL;
core::binding::TFunction<u32_t (u32_t shaderType)> Extension::glCreateShaderObject = NULL;
core::binding::TFunction<void (u32_t obj)> Extension::glDeleteShaderObject = NULL;
core::binding::TFunction<void (u32_t shaderObj, s32_t count, lpcstr_t * string, const s32_t * length)> Extension::glShaderSource = NULL;
core::binding::TFunction<void (u32_t shaderObj)> Extension::glCompileShader = NULL;
core::binding::TFunction<void (u32_t obj, u32_t pname, s32_t * params)> Extension::glGetObjectParameteriv = NULL;
core::binding::TFunction<void (u32_t obj, s32_t maxLength, s32_t * length, lpstr_t infoLog)> Extension::glGetInfoLog = NULL;

core::binding::TFunction<void (s32_t num, u32_t * buffers)> Extension::glGenBuffers = NULL;
core::binding::TFunction<void (s32_t num, const u32_t * buffers)> Extension::glDeleteBuffers = NULL;
core::binding::TFunction<void (u32_t target, u32_t buffer)> Extension::glBindBuffer = NULL;
core::binding::TFunction<void (u32_t target, ptrdiff_t size, const void * data, u32_t usage)> Extension::glBufferData = NULL;
core::binding::TFunction<void (u32_t target, ptrdiff_t offset, ptrdiff_t size, const void * data)> Extension::glBufferSubData = NULL;
core::binding::TFunction<void * (u32_t target, u32_t access)> Extension::glMapBuffer = NULL;
core::binding::TFunction<u8_t (u32_t target)> Extension::glUnmapBuffer = NULL;
core::binding::TFunction<u8_t (u32_t buffer)> Extension::glIsBuffer = NULL;
core::binding::TFunction<void (u32_t target, u32_t pname, s32_t * params)> Extension::glGetBufferParameteriv = NULL;

core::binding::TFunction<s32_t (u32_t programObj, lpcstr_t name)> Extension::glGetAttribLocation = NULL;
core::binding::TFunction<void (u32_t index)> Extension::glEnableVertexAttribArray = NULL;
core::binding::TFunction<void (u32_t index)> Extension::glDisableVertexAttribArray = NULL;
core::binding::TFunction<void (u32_t index, s32_t size, u32_t type, u8_t normalized, s32_t stride, const void * pointer)> Extension::glVertexAttribPointer = NULL;

void Extension::define(const boost::function<core::binding::ProcAddress_t (ExtensionInitList_t)> & loadExtension) {
	glCreateProgramObject = loadExtension({{ "GL_ARB_shader_objects", "glCreateProgramObjectARB" }});
	glDeletePrograms = loadExtension({{ "GL_ARB_fragment_program", "glDeleteProgramsARB" }});
	glAttachObject = loadExtension({{ "GL_ARB_shader_objects", "glAttachObjectARB" }});
	glDetachObject = loadExtension({{ "GL_ARB_shader_objects", "glDetachObjectARB" }});
	glLinkProgram = loadExtension({{ "GL_ARB_shader_objects", "glLinkProgramARB" }});
	glValidateProgram = loadExtension({{ "GL_ARB_shader_objects", "glValidateProgramARB" }});
	glUseProgramObject = loadExtension({{ "GL_ARB_shader_objects", "glUseProgramObjectARB" }});
	glGetUniformLocation = loadExtension({{ "GL_ARB_shader_objects", "glGetUniformLocationARB" }});
	glUniform4f = loadExtension({{ "GL_ARB_shader_objects", "glUniform4fARB" }});
	glCreateShaderObject = loadExtension({{ "GL_ARB_shader_objects", "glCreateShaderObjectARB" }});
	glDeleteShaderObject = loadExtension({{ "GL_ARB_shader_objects", "glDeleteObjectARB" }});
	glShaderSource = loadExtension({{ "GL_ARB_shader_objects", "glShaderSourceARB" }});
	glCompileShader = loadExtension({{ "GL_ARB_shader_objects", "glCompileShaderARB" }});
	glGetObjectParameteriv = loadExtension({{ "GL_ARB_shader_objects", "glGetObjectParameterivARB" }});
	glGetInfoLog = loadExtension({{ "GL_ARB_shader_objects", "glGetInfoLogARB" }});

	glGenBuffers = loadExtension({{ "GL_ARB_vertex_buffer_object", "glGenBuffersARB" }});
	glDeleteBuffers = loadExtension({{ "GL_ARB_vertex_buffer_object", "glDeleteBuffersARB" }});
	glBindBuffer = loadExtension({{ "GL_ARB_vertex_buffer_object", "glBindBufferARB" }});
	glBufferData = loadExtension({{ "GL_ARB_vertex_buffer_object", "glBufferDataARB" }});
	glBufferSubData = loadExtension({{ "GL_ARB_vertex_buffer_object", "glBufferSubDataARB" }});
	glMapBuffer = loadExtension({{ "GL_ARB_vertex_buffer_object", "glMapBufferARB" }});
	glUnmapBuffer = loadExtension({{ "GL_ARB_vertex_buffer_object", "glUnmapBufferARB" }});
	glIsBuffer = loadExtension({{ "GL_ARB_vertex_buffer_object", "glIsBufferARB" }});
	glGetBufferParameteriv = loadExtension({{ "GL_ARB_vertex_buffer_object", "glGetBufferParameterivARB" }});

	glGetAttribLocation = loadExtension({{ "GL_ARB_vertex_shader", "glGetAttribLocationARB" }});
	glEnableVertexAttribArray = loadExtension({{ "GL_ARB_vertex_program", "glEnableVertexAttribArrayARB" }});
	glDisableVertexAttribArray = loadExtension({{ "GL_ARB_vertex_program", "glDisableVertexAttribArrayARB" }});
	glVertexAttribPointer = loadExtension({{ "GL_ARB_vertex_program", "glVertexAttribPointerARB" }});
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
