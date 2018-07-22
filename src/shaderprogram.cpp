#include <sway/gapi/gl/shaderprogram.h>
#include <sway/gapi/gl/shaderexceptions.h>
#include <sway/gapi/gl/shaderutils.h>
#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

ShaderProgram::ShaderProgram()
	: _linked(false)
	, _validated(false) {
	_objectId = Extensions::glCreateProgramObjectARB();
}

ShaderProgram::~ShaderProgram() {
	std::for_each(_shaderIdSet.begin(), _shaderIdSet.end(), std::bind(&ShaderProgram::detach, this, std::placeholders::_1));
	Extensions::glDeleteProgramsARB(1, &_objectId);
}

void ShaderProgram::attach(IShaderBase * shader) {
	auto result = _shaderIdSet.insert(shader->getObjectId());
	if (result.second)
		Extensions::glAttachObjectARB(_objectId, *(result.first));
}

void ShaderProgram::detach(u32_t shaderId) {
	Extensions::glDetachObjectARB(_objectId, shaderId);
	_shaderIdSet.erase(shaderId);
}

void ShaderProgram::link() {
	int linkStatus;
	Extensions::glLinkProgramARB(_objectId);
	Extensions::glGetObjectParameterivARB(_objectId, GL_OBJECT_LINK_STATUS_ARB, &linkStatus);
	_linked = (linkStatus == GL_TRUE);
	if (!_linked)
		throw ShaderLinkageException(ShaderUtils::getErrorInfo(_objectId));
}

bool ShaderProgram::isLinked() const {
	return _linked;
}

void ShaderProgram::validate() {
	int validateStatus;
	Extensions::glValidateProgramARB(_objectId);
	Extensions::glGetObjectParameterivARB(_objectId, GL_OBJECT_VALIDATE_STATUS_ARB, &validateStatus);
	_validated = (validateStatus == GL_TRUE);
	if (!_validated)
		throw ShaderValidationException(ShaderUtils::getErrorInfo(_objectId));
}

bool ShaderProgram::isValidated() const {
	return _validated;
}

void ShaderProgram::use() {
	if (_objectId > 0 && !isUsed()) {
		Extensions::glUseProgramObjectARB(_objectId);

		for (auto iter : _uniformVec4fSet) {
			s32_t location = Extensions::glGetUniformLocationARB(_objectId, iter.first.c_str());
			if (location != -1)
				Extensions::glUniform4fARB(location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
		}
	}
}

void ShaderProgram::unuse() {
	if (_objectId > 0 && isUsed())
		Extensions::glUseProgramObjectARB(0);
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

u32_t ShaderProgram::getObjectId() const {
	return _objectId;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)