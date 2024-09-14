#include <sway/gapi/gl/oglshaderpreprocessor.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLShaderPreprocessor::createInstance(u32_t major, lpcstr_t profile) -> ShaderPreprocessor::Ptr_t {
  auto instance = new OGLShaderPreprocessor(core::Version(major, DONT_CARE, DONT_CARE, profile));
  return instance;
}

OGLShaderPreprocessor::OGLShaderPreprocessor(const core::Version &version)
    : version_(version) {}

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
  into << "#version " << version_.getMajor() << " " << version_.getExtra() << std::endl;

  for (const auto &item : definitions_) {
    into << "#define " << item.first << " " << item.second << std::endl;
  }
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
