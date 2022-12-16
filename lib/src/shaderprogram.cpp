#include <sway/gapi/gl/exceptions.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/genericshader.hpp>
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
    : shaderHelper_(gapi::Extension::extensions)
    , programHelper_(gapi::Extension::extensions)
    , linked_(false)
    , validated_(false) {
  auto objectId = programHelper_.CreateProgram();
  if (objectId != 0) {
    setUid(objectId);
  }
}

ShaderProgram::~ShaderProgram() {
  std::for_each(
      objectIdSet_.begin(), objectIdSet_.end(), std::bind(&ShaderProgram::detach, this, std::placeholders::_1));

  auto programId = getUid().value();
  programHelper_.DeleteProgram(1, &programId);
}

void ShaderProgram::attach(ShaderRef_t shader) {
  auto result = objectIdSet_.insert(shader->getUid().value());
  if (result.second) {
    programHelper_.AttachShader(getUid().value(), *(result.first));
  }
}

void ShaderProgram::detach(u32_t attachedId) {
  programHelper_.DetachShader(getUid().value(), attachedId);
  objectIdSet_.erase(attachedId);
}

void ShaderProgram::link() {
  int linkStatus;

  programHelper_.LinkProgram(getUid().value());
  programHelper_.GetObjectParam(getUid().value(), GL_LINK_STATUS, &linkStatus);  // GL_OBJECT_LINK_STATUS_ARB
  linked_ = (linkStatus == GL_TRUE);
  if (!linked_) {
    throw ShaderProgramLinkageException(getUid().value());
  }
}

void ShaderProgram::validate() {
  int validateStatus;

  programHelper_.ValidateProgram(getUid().value());
  programHelper_.GetObjectParam(
      getUid().value(), GL_VALIDATE_STATUS, &validateStatus);  // GL_OBJECT_VALIDATE_STATUS_ARB
  validated_ = (validateStatus == GL_TRUE);
  if (!validated_) {
    throw ShaderProgramValidationException(getUid().value());
  }
}

void ShaderProgram::use() {
  if (getUid().value() > 0 && !isUsed()) {
    programHelper_.UseProgram(getUid().value());

    for (auto iter : uniformVec4fSet_) {
      auto location = programHelper_.GetUniformLocation(getUid().value(), iter.first.c_str());
      if (location != -1) {
        programHelper_.Uniform4f(
            location, iter.second.getX(), iter.second.getY(), iter.second.getZ(), iter.second.getW());
      }
    }

    for (auto iter : uniformMat4fSet_) {
      auto location = programHelper_.GetUniformLocation(getUid().value(), iter.first.c_str());
      if (location != -1) {
        programHelper_.UniformMatrix4f(location, 1, GL_FALSE, (float *)&iter.second);
      }
    }
  }
}

void ShaderProgram::unuse() {
  if (getUid().value() > 0 && isUsed()) {
    programHelper_.UseProgram(0);
  }
}

auto ShaderProgram::isUsed() const -> bool {
  s32_t current = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &current);

  return (current == (s32_t)getUid().value());
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
