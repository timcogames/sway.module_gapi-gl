#include <sway/gapi/gl/shader.h>
#include <sway/gapi/gl/extensions.h>
#include <sway/gapi/gl/exceptions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

DLLAPI_EXPORT ShaderRef_t createShader(const ShaderCreateInfo & createInfo) {
	try {
		auto instance = boost::make_shared<Shader>(createInfo.type);
		instance->compile(createInfo.code.c_str());
		return instance;
	}
	catch (std::exception & exception) {
		fprintf(stderr, "ERROR: %s shader object creation failed.\n", stringize(createInfo.type).c_str());
		throw;
	}
}

GLenum Shader::typeToGLenum(ShaderType_t type) {
	switch (type) {
	case ShaderType_t::kVertex: return GL_VERTEX_SHADER_ARB;
	case ShaderType_t::kFragment: return GL_FRAGMENT_SHADER_ARB;
	default:
		return GL_INVALID_INDEX;
	}
}

Shader::Shader(ShaderType_t type) : AShaderBase(type)
	, _type(type)
	, _compiled(false) {
	_objectId = Extension::glCreateShaderObject(Shader::typeToGLenum(_type));
}

Shader::~Shader() {
	Extension::glDeleteShaderObject(_objectId);
}

void Shader::compile(lpcstr_t source) {
	int compileStatus;
	Extension::glShaderSource(_objectId, 1, &source, NULL);
	Extension::glCompileShader(_objectId);
	Extension::glGetObjectParameteriv(_objectId, GL_OBJECT_COMPILE_STATUS_ARB, &compileStatus);
	_compiled = (compileStatus == GL_TRUE);
	if (!_compiled)
		throw ShaderCompilationException(_objectId);
}

bool Shader::isCompiled() const {
	return _compiled;
}

ShaderType_t Shader::getType() const {
	return _type;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
