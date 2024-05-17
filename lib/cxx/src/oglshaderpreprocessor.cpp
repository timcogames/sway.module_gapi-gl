#include <sway/gapi/gl/oglshaderpreprocessor.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

OGLShaderPreprocessor::OGLShaderPreprocessor(ShaderType type, const core::Version &version)
    : type_(type)
    , version_(version) {}

void OGLShaderPreprocessor::addDefine(const std::string &name, const std::string &val) {
  if (name.empty()) {
    return;
  }

  definitions_[name] = val;
}

auto OGLShaderPreprocessor::hasDefined(const std::string &name) const -> bool {
  return definitions_.find(name) != definitions_.end();
}

void OGLShaderPreprocessor::evaluate(std::ostream &into) {
  into << "#version " << version_.getMajor();
  auto profile = version_.getExtra();
  if (!profile.empty()) {
    into << " " << profile;
  }

  into << std::endl;

  if (type_ == ShaderType::FRAG) {
    into << "#ifdef GL_FRAGMENT_PRECISION_HIGH" << std::endl;
    into << "  precision highp float;" << std::endl;
    into << "#else" << std::endl;
    into << "  precision mediump float;" << std::endl;
    into << "#endif" << std::endl;
  }

  for (const auto &[key, val] : definitions_) {
    into << "#define " << key << " " << val << std::endl;
  }
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
