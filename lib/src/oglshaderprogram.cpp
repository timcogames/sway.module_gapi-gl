#include <sway/gapi/gl/oglexceptions.hpp>
#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/oglgenericshader.hpp>
#include <sway/gapi/gl/oglshaderprogram.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLShaderProgram::createInstance() -> ShaderProgramRef_t {
  auto instance = std::make_shared<OGLShaderProgram>();
  return instance;
}

OGLShaderProgram::OGLShaderProgram()
    : helper_(gapi::Extension::extensions)
    , linked_(false)
    , validated_(false) {
  auto objectId = helper_.CreateProgram();
  if (objectId != 0) {
    setUid(objectId);
  }
}

OGLShaderProgram::~OGLShaderProgram() {
  // glGetAttachedShaders
  std::for_each(shaders_.begin(), shaders_.end(), [this](auto pair) { detach(pair, false); });
  shaders_.clear();

  auto programId = getUid().value();
  helper_.DeleteProgram(1, &programId);
}

void OGLShaderProgram::attach(ShaderRef_t shader) {
  // glIsShader
  shaders_.insert(std::make_pair(shader->getType(), shader));
  helper_.AttachShader(getUid(), shader->getUid());
}

void OGLShaderProgram::detach(std::pair<ShaderType, ShaderRef_t> pair, bool erasing) {
  helper_.DetachShader(getUid(), pair.second->getUid());
  if (erasing) {
    shaders_.erase(pair.first);
  }
}

auto OGLShaderProgram::getShader(ShaderType type) -> ShaderRef_t {
  auto iter = shaders_.find(type);
  if (iter != shaders_.end()) {
    return iter->second;
  }

  return nullptr;
}

void OGLShaderProgram::link() {
  int status;  // Состояние шагов линковки.
  helper_.LinkProgram(getUid(), &status);
  linked_ = (status == GL_TRUE);
  if (!linked_) {
    throw OGLShaderProgramLinkageException(getUid().value());
  }
}

void OGLShaderProgram::validate() {
  int status;
  helper_.ValidateProgram(getUid(), &status);
  validated_ = (status == GL_TRUE);
  if (!validated_) {
    throw OGLShaderProgramValidationException(getUid().value());
  }
}

void OGLShaderProgram::use() {
  if (getUid().value() > 0 && !isUsed()) {
    helper_.UseProgram(getUid());

    for (auto iter : uniformVec4fSet_) {
      auto location = helper_.GetUniformLocation(getUid(), iter.first.c_str());
      if (location != -1) {
        helper_.Uniform4f(location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
      }
    }

    for (auto iter : uniformMat4fSet_) {
      auto location = helper_.GetUniformLocation(getUid(), iter.first.c_str());
      if (location != -1) {
        helper_.UniformMatrix4f(location, 1, false, (float *)&iter.second);
      }
    }

    for (auto iter : uniform1iSet_) {
      auto location = helper_.GetUniformLocation(getUid(), iter.first.c_str());
      if (location != -1) {
        helper_.Uniform1i(location, iter.second);
      }
    }
  }
}

void OGLShaderProgram::unuse() {
  if (getUid().value() > 0 && isUsed()) {
    helper_.UseProgram(0);
  }
}

auto OGLShaderProgram::isUsed() const -> bool {
  s32_t current = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &current);

  return (current == (s32_t)getUid().value());
}

void OGLShaderProgram::setUniformVec4f(const std::string &uniform, const math::vec4f_t &vec) {
  uniformVec4fSet_[uniform] = vec;
}

void OGLShaderProgram::setUniformCol4f(const std::string &uniform, const math::col4f_t &col) {
  uniformVec4fSet_[uniform] = col.toVec4();
}

void OGLShaderProgram::setUniformMat4f(const std::string &uniform, const math::mat4f_t &mat) {
  uniformMat4fSet_[uniform] = mat;
}

void OGLShaderProgram::setUniform1i(const std::string &uniform, s32_t val) { uniform1iSet_[uniform] = val; }

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
