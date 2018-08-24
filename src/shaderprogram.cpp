#include <sway/gapi/gl/shaderprogram.h>
#include <sway/gapi/gl/shader.h>
#include <sway/gapi/gl/extensions.h>
#include <sway/gapi/gl/exceptions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

DLLAPI_EXPORT ShaderProgramRef_t createShaderProgram() {
	auto instance = boost::make_shared<ShaderProgram>();
	return instance;
}

ShaderProgram::ShaderProgram()
	: _linked(false)
	, _validated(false) {
	_objectId = Extension::glCreateProgramObject();
}

ShaderProgram::~ShaderProgram() {
	std::for_each(_objectIdSet.begin(), _objectIdSet.end(), std::bind(&ShaderProgram::detach, this, std::placeholders::_1));
	Extension::glDeletePrograms(1, &_objectId);
}

void ShaderProgram::attach(ShaderRef_t shader) {
	auto result = _objectIdSet.insert(shader->getObjectId());
	if (result.second)
		Extension::glAttachObject(_objectId, *(result.first));
}

void ShaderProgram::detach(u32_t attachedId) {
	Extension::glDetachObject(_objectId, attachedId);
	_objectIdSet.erase(attachedId);
}

void ShaderProgram::link() {
	int linkStatus;
	Extension::glLinkProgram(_objectId);
	Extension::glGetObjectParameteriv(_objectId, GL_OBJECT_LINK_STATUS_ARB, &linkStatus);
	_linked = (linkStatus == GL_TRUE);
	if (!_linked)
		throw ShaderProgramLinkageException(_objectId);
}

bool ShaderProgram::isLinked() const {
	return _linked;
}

void ShaderProgram::validate() {
	int validateStatus;
	Extension::glValidateProgram(_objectId);
	Extension::glGetObjectParameteriv(_objectId, GL_OBJECT_VALIDATE_STATUS_ARB, &validateStatus);
	_validated = (validateStatus == GL_TRUE);
	if (!_validated)
		throw ShaderProgramValidationException(_objectId);
}

bool ShaderProgram::isValidated() const {
	return _validated;
}

void ShaderProgram::use() {
	if (_objectId > 0 && !isUsed()) {
		Extension::glUseProgramObject(_objectId);

		for (auto iter : _uniformVec4fSet) {
			s32_t location = Extension::glGetUniformLocation(_objectId, iter.first.c_str());
			if (location != -1)
				Extension::glUniform4f(location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
		}
	}
}

void ShaderProgram::unuse() {
	if (_objectId > 0 && isUsed())
		Extension::glUseProgramObject(0);
}

bool ShaderProgram::isUsed() const {
	s32_t current = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &current);

	return (current == (s32_t)_objectId);
}

void ShaderProgram::setUniformVec4f(const std::string & uniform, const math::vec4f_t & vec) {
	_uniformVec4fSet[uniform] = vec;
}

void ShaderProgram::setUniformCol4f(const std::string & uniform, const math::col4f_t & col) {
	_uniformVec4fSet[uniform] = col.toVec4();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
