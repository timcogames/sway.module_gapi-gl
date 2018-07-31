#include <sway/gapi/gl/shaderobject.h>
#include <sway/gapi/gl/shaderexceptions.h>
#include <sway/gapi/gl/shaderutils.h>
#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

EXTERN_C_BEGIN

IShaderBase * createShader(const ShaderCreateInfo & createInfo) {
	try {
		IShaderBase * instance = new ShaderObject(createInfo.type);
		instance->compile(createInfo.source.c_str());
		return instance;
	} catch (std::exception & exception) {
		fprintf(stderr, "ERROR: %s shader object creation failed.\n", ShaderObject::typeToStr(createInfo.type).c_str());
		throw;
	}
}

EXTERN_C_END

GLenum ShaderObject::typeToGLenum(ShaderType_t type) {
	switch (type) {
	case ShaderType_t::kVertex: return GL_VERTEX_SHADER_ARB;
	case ShaderType_t::kFragment: return GL_FRAGMENT_SHADER_ARB;
	default:
		return GL_INVALID_INDEX;
	}
}

std::string ShaderObject::typeToStr(ShaderType_t type) {
	switch (type) {
	case ShaderType_t::kVertex: return "Vertex"; 
	case ShaderType_t::kFragment: return "Fragment"; 
	default:
		return "Undefined";
	}
}

ShaderObject::ShaderObject(ShaderType_t type) : IShaderBase(type)
	, _type(type)
	, _compiled(false) {
	_objectId = Extensions::glCreateShaderObjectARB(ShaderObject::typeToGLenum(_type));
}

ShaderObject::~ShaderObject() {
	Extensions::glDeleteObjectARB(_objectId);
}

void ShaderObject::compile(lpcstr_t source) {
	int compileStatus;
	Extensions::glShaderSourceARB(_objectId, 1, &source, NULL);
	Extensions::glCompileShaderARB(_objectId);
	Extensions::glGetObjectParameterivARB(_objectId, GL_OBJECT_COMPILE_STATUS_ARB, &compileStatus);
	_compiled = (compileStatus == GL_TRUE);
	if (!_compiled)
		throw ShaderCompilationException(ShaderUtils::getErrorInfo(_objectId));
}

bool ShaderObject::isCompiled() const {
	return _compiled;
}

ShaderType_t ShaderObject::getType() const {
	return _type;
}

u32_t ShaderObject::getObjectId() const {
	return _objectId;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
