#include <sway/gapi/shaderprogram.h>
#include <sway/gapi/shaderexceptions.h>
#include <sway/gapi/shaderutils.h>
#include <sway/gapi/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

ShaderProgram::ShaderProgram()
	: _linked(false)
	, _validated(false) {
	_resourceId = Extensions::glCreateProgramObjectARB();
}

ShaderProgram::~ShaderProgram() {
	std::for_each(_shaderSet.begin(), _shaderSet.end(), std::bind(&ShaderProgram::detach, this, std::placeholders::_1));
	Extensions::glDeleteProgramsARB(1, &_resourceId);
}

void ShaderProgram::attach(ShaderObject * shader) {
	auto result = _shaderSet.insert(shader->getId());
	if (result.second)
		Extensions::glAttachObjectARB(_resourceId, *(result.first));
}

void ShaderProgram::detach(ResourceId_t shaderId) {
	Extensions::glDetachObjectARB(_resourceId, shaderId);
	_shaderSet.erase(shaderId);
}

void ShaderProgram::link() {
	int linkStatus;
	Extensions::glLinkProgramARB(_resourceId);
	Extensions::glGetObjectParameterivARB(_resourceId, GL_OBJECT_LINK_STATUS_ARB, &linkStatus);
	_linked = (linkStatus == GL_TRUE);
	if (!_linked)
		throw ShaderLinkageException(ShaderUtils::getErrorInfo(_resourceId));
}

bool ShaderProgram::isLinked() const {
	return _linked;
}

void ShaderProgram::validate() {
	int validateStatus;
	Extensions::glValidateProgramARB(_resourceId);
	Extensions::glGetObjectParameterivARB(_resourceId, GL_OBJECT_VALIDATE_STATUS_ARB, &validateStatus);
	_validated = (validateStatus == GL_TRUE);
	if (!_validated)
		throw ShaderValidationException(ShaderUtils::getErrorInfo(_resourceId));
}

bool ShaderProgram::isValidated() const {
	return _validated;
}

void ShaderProgram::use() {
	if (_resourceId > 0 && !isUsed()) {
		Extensions::glUseProgramObjectARB(_resourceId);

		for (auto iter : _uniformVec4fSet) {
			s32_t location = Extensions::glGetUniformLocationARB(_resourceId, iter.first.c_str());
			if (location != -1)
				Extensions::glUniform4fARB(location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
		}
	}
}

void ShaderProgram::unuse() {
	if (_resourceId > 0 && isUsed())
		Extensions::glUseProgramObjectARB(0);
}

bool ShaderProgram::isUsed() const {
	s32_t current = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &current);

	return (current == (s32_t)_resourceId);
}

void ShaderProgram::setUniformVec4f(const std::string & uniform, const math::vec4f_t & vec) {
	_uniformVec4fSet[uniform] = vec;
}

void ShaderProgram::setUniformCol4f(const std::string & uniform, const math::col4f_t & col) {
	_uniformVec4fSet[uniform] = col.toVec4();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
