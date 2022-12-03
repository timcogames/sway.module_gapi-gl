#include <sway/gapi/gl/exceptions.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/shader.hpp>
#include <sway/gapi/gl/shaderprogram.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto ShaderProgram::createInstance() -> ShaderProgramRef_t {
  auto instance = std::make_shared<ShaderProgram>();
  return instance;
}

ShaderProgram::ShaderProgram()
    : _linked(false)
    , _validated(false) {
#ifdef _EMSCRIPTEN
  _objectId = glCreateProgram();
#else
  _objectId = Extension::glCreateProgramObject();
#endif
}

ShaderProgram::~ShaderProgram() {
  std::for_each(
      _objectIdSet.begin(), _objectIdSet.end(), std::bind(&ShaderProgram::detach, this, std::placeholders::_1));

#ifdef _EMSCRIPTEN
  glDeleteProgram(_objectId);
#else
  Extension::glDeletePrograms(1, &_objectId);
#endif
}

void ShaderProgram::attach(ShaderRef_t shader) {
  int shaderObjectId = shader->getObjectId();
  // std::set<int> s1;
  // s1.insert(shader->getObjectId());
  //_objectIdSet.insert(s1.begin(), s1.end());

  auto result = _objectIdSet.insert(shaderObjectId);
  if (result.second) {
#ifdef _EMSCRIPTEN
    glAttachShader(_objectId, *(result.first));
    // glAttachShader(_objectId, shader->getObjectId());
#else
    Extension::glAttachObject(_objectId, *(result.first));
#endif
  }
}

void ShaderProgram::detach(u32_t attachedId) {
#ifdef _EMSCRIPTEN
  glDetachShader(_objectId, attachedId);
#else
  Extension::glDetachObject(_objectId, attachedId);
#endif

  _objectIdSet.erase(attachedId);
}

void ShaderProgram::link() {
  int linkStatus;

#ifdef _EMSCRIPTEN
  glLinkProgram(_objectId);
  glGetProgramiv(_objectId, GL_LINK_STATUS, &linkStatus);
#else
  Extension::glLinkProgram(_objectId);
  Extension::glGetObjectParameteriv(_objectId, GL_OBJECT_LINK_STATUS_ARB, &linkStatus);
#endif

  _linked = (linkStatus == GL_TRUE);
  if (!_linked) {
    throw ShaderProgramLinkageException(_objectId);
  }
}

auto ShaderProgram::isLinked() const -> bool { return _linked; }

void ShaderProgram::validate() {
  int validateStatus;

#ifdef _EMSCRIPTEN
  glValidateProgram(_objectId);
  glGetProgramiv(_objectId, GL_VALIDATE_STATUS, &validateStatus);
#else
  Extension::glValidateProgram(_objectId);
  Extension::glGetObjectParameteriv(_objectId, GL_OBJECT_VALIDATE_STATUS_ARB, &validateStatus);
#endif

  _validated = (validateStatus == GL_TRUE);
  if (!_validated) {
    throw ShaderProgramValidationException(_objectId);
  }
}

auto ShaderProgram::isValidated() const -> bool { return _validated; }

void ShaderProgram::use() {
  if (_objectId > 0 && !isUsed()) {

#ifdef _EMSCRIPTEN
    glUseProgram(_objectId);
    for (auto iter : _uniformVec4fSet) {
      s32_t location = glGetUniformLocation(_objectId, iter.first.c_str());
      if (location != -1) {
        glUniform4f(location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
      }
    }
#else
    Extension::glUseProgramObject(_objectId);
    for (auto iter : _uniformVec4fSet) {
      s32_t location = Extension::glGetUniformLocation(_objectId, iter.first.c_str());
      if (location != -1) {
        Extension::glUniform4f(
            location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
      }
    }
#endif
  }
}

void ShaderProgram::unuse() {
  if (_objectId > 0 && isUsed()) {
#ifdef _EMSCRIPTEN
    glUseProgram(0);
#else
    Extension::glUseProgramObject(0);
#endif
  }
}

auto ShaderProgram::isUsed() const -> bool {
  s32_t current = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &current);

  return (current == (s32_t)_objectId);
}

void ShaderProgram::setUniformVec4f(const std::string &uniform, const math::vec4f_t &vec) {
  _uniformVec4fSet[uniform] = vec;
}

void ShaderProgram::setUniformCol4f(const std::string &uniform, const math::col4f_t &col) {
  _uniformVec4fSet[uniform] = col.toVec4();
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
