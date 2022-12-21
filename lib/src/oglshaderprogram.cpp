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
  std::for_each(
      objectIdSet_.begin(), objectIdSet_.end(), std::bind(&OGLShaderProgram::detach, this, std::placeholders::_1));

  auto programId = getUid().value();
  helper_.DeleteProgram(1, &programId);
}

void OGLShaderProgram::attach(ShaderRef_t shader) {
  auto result = objectIdSet_.insert(shader->getUid().value());
  if (result.second) {
    helper_.AttachShader(getUid().value(), *(result.first));
  }
}

void OGLShaderProgram::detach(u32_t attachedId) {
  helper_.DetachShader(getUid().value(), attachedId);
  objectIdSet_.erase(attachedId);
}

void OGLShaderProgram::link() {
  int linkStatus;

  helper_.LinkProgram(getUid().value());
  helper_.GetObjectParam(getUid().value(), GL_LINK_STATUS, &linkStatus);  // GL_OBJECT_LINK_STATUS_ARB
  linked_ = (linkStatus == GL_TRUE);
  if (!linked_) {
    throw OGLShaderProgramLinkageException(getUid().value());
  }
}

void OGLShaderProgram::validate() {
  int validateStatus;

  helper_.ValidateProgram(getUid().value());
  helper_.GetObjectParam(getUid().value(), GL_VALIDATE_STATUS, &validateStatus);  // GL_OBJECT_VALIDATE_STATUS_ARB
  validated_ = (validateStatus == GL_TRUE);
  if (!validated_) {
    throw OGLShaderProgramValidationException(getUid().value());
  }
}

void OGLShaderProgram::use() {
  if (getUid().value() > 0 && !isUsed()) {
    helper_.UseProgram(getUid().value());

    for (auto iter : uniformVec4fSet_) {
      auto location = helper_.GetUniformLocation(getUid().value(), iter.first.c_str());
      if (location != -1) {
        helper_.Uniform4f(location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
      }
    }

    for (auto iter : uniformMat4fSet_) {
      auto location = helper_.GetUniformLocation(getUid().value(), iter.first.c_str());
      if (location != -1) {
        helper_.UniformMatrix4f(location, 1, false, (float *)&iter.second);
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

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
