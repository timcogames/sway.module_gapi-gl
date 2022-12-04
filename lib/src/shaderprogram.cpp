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
    : linked_(false)
    , validated_(false) {
#ifdef _EMSCRIPTEN
  objectId_ = glCreateProgram();
#else
  objectId_ = Extension::glCreateProgramObject();
#endif
}

ShaderProgram::~ShaderProgram() {
  std::for_each(
      objectIdSet_.begin(), objectIdSet_.end(), std::bind(&ShaderProgram::detach, this, std::placeholders::_1));

#ifdef _EMSCRIPTEN
  glDeleteProgram(objectId_);
#else
  Extension::glDeletePrograms(1, &objectId_);
#endif
}

void ShaderProgram::attach(ShaderRef_t shader) {
  int shaderObjectId = shader->getObjectId();
  // std::set<int> s1;
  // s1.insert(shader->getObjectId());
  // objectIdSet_.insert(s1.begin(), s1.end());

  auto result = objectIdSet_.insert(shaderObjectId);
  if (result.second) {
#ifdef _EMSCRIPTEN
    glAttachShader(objectId_, *(result.first));
    // glAttachShader(objectId_, shader->getObjectId());
#else
    Extension::glAttachObject(objectId_, *(result.first));
#endif
  }
}

void ShaderProgram::detach(u32_t attachedId) {
#ifdef _EMSCRIPTEN
  glDetachShader(objectId_, attachedId);
#else
  Extension::glDetachObject(objectId_, attachedId);
#endif

  objectIdSet_.erase(attachedId);
}

void ShaderProgram::link() {
  int linkStatus;

#ifdef _EMSCRIPTEN
  glLinkProgram(objectId_);
  glGetProgramiv(objectId_, GL_LINK_STATUS, &linkStatus);
#else
  Extension::glLinkProgram(objectId_);
  Extension::glGetObjectParameteriv(objectId_, GL_OBJECT_LINK_STATUS_ARB, &linkStatus);
#endif

  linked_ = (linkStatus == GL_TRUE);
  if (!linked_) {
    throw ShaderProgramLinkageException(objectId_);
  }
}

auto ShaderProgram::isLinked() const -> bool { return linked_; }

void ShaderProgram::validate() {
  int validateStatus;

#ifdef _EMSCRIPTEN
  glValidateProgram(objectId_);
  glGetProgramiv(objectId_, GL_VALIDATE_STATUS, &validateStatus);
#else
  Extension::glValidateProgram(objectId_);
  Extension::glGetObjectParameteriv(objectId_, GL_OBJECT_VALIDATE_STATUS_ARB, &validateStatus);
#endif

  validated_ = (validateStatus == GL_TRUE);
  if (!validated_) {
    throw ShaderProgramValidationException(objectId_);
  }
}

auto ShaderProgram::isValidated() const -> bool { return validated_; }

void ShaderProgram::use() {
  if (objectId_ > 0 && !isUsed()) {

#ifdef _EMSCRIPTEN
    glUseProgram(objectId_);

    for (auto iter : uniformVec4fSet_) {
      s32_t location = glGetUniformLocation(objectId_, iter.first.c_str());
      if (location != -1) {
        glUniform4f(location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
      }
    }
#else
    Extension::glUseProgramObject(objectId_);

    for (auto iter : uniformVec4fSet_) {
      s32_t location = Extension::glGetUniformLocation(objectId_, iter.first.c_str());
      if (location != -1) {
        Extension::glUniform4f(
            location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
      }
    }

    for (auto iter : uniformMat4fSet_) {
      s32_t location = Extension::glGetUniformLocation(objectId_, iter.first.c_str());
      if (location != -1) {
        Extension::glUniformMatrix4fv(location, 1, GL_FALSE, (float *)&iter.second);
      }
    }
#endif
  }
}

void ShaderProgram::unuse() {
  if (objectId_ > 0 && isUsed()) {
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

  return (current == (s32_t)objectId_);
}

void ShaderProgram::setUniformVec4f(const std::string &uniform, const math::vec4f_t &vec) {
  uniformVec4fSet_[uniform] = vec;
}

void ShaderProgram::setUniformCol4f(const std::string &uniform, const math::col4f_t &col) {
  uniformVec4fSet_[uniform] = col.toVec4();
}

void ShaderProgram::setUniformMat4f(const std::string &uniform, const math::mat4f_t &mat) {
  uniformMat4fSet_[uniform] = mat;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
