#include <sway/gapi/shaderobject.h>
#include <sway/gapi/shaderexceptions.h>
#include <sway/gapi/shaderutils.h>
#include <sway/gapi/shadertypes.h>
#include <sway/gapi/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

GLenum ShaderObject::typeToGLenum(u32_t type) {
	switch (type) {
	case kShaderType_Vertex: return GL_VERTEX_SHADER_ARB;
	case kShaderType_Fragment: return GL_FRAGMENT_SHADER_ARB;
	default:
		return 0;
	}
}

std::string ShaderObject::typeToStr(u32_t type) {
	switch (type) {
	case kShaderType_Vertex: return "Vertex"; 
	case kShaderType_Fragment: return "Fragment"; 
	default:
		return "Undefined";
	}
}

ShaderObject * ShaderObject::create(const ShaderObjectCreateInfo & createInfo) {
	try {
		ShaderObject * instance = new ShaderObject(createInfo.type);
		instance->compile(createInfo.source.c_str());
		return instance;
	} catch (std::exception & exception) {
		fprintf(stderr, "ERROR: %s shader object creation failed.\n", ShaderObject::typeToStr(createInfo.type).c_str());
		throw;
	}
}

ShaderObject::ShaderObject(u32_t type)
	: _type(type)
	, _compiled(false) {
	_resourceId = Extensions::glCreateShaderObjectARB(ShaderObject::typeToGLenum(_type));
}

ShaderObject::~ShaderObject() {
	Extensions::glDeleteObjectARB(_resourceId);
}

void ShaderObject::compile(lpcstr_t source) {
	int compileStatus;
	Extensions::glShaderSourceARB(_resourceId, 1, &source, NULL);
	Extensions::glCompileShaderARB(_resourceId);
	Extensions::glGetObjectParameterivARB(_resourceId, GL_OBJECT_COMPILE_STATUS_ARB, &compileStatus);
	_compiled = (compileStatus == GL_TRUE);
	if (!_compiled)
		throw ShaderCompilationException(ShaderUtils::getErrorInfo(_resourceId));
}

bool ShaderObject::isCompiled() const {
	return _compiled;
}

u32_t ShaderObject::getType() const {
	return _type;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
