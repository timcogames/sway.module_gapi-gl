#include <sway/gapi/gl/oglshaderpreprocessor.hpp>

namespace sway::gapi {

auto OGLShaderPreprocessor::createInstance(u32_t major, lpcstr_t profile) -> typedefs::ShaderPreprocessorPtr_t {
  auto instance = new OGLShaderPreprocessor(core::Version(major, GLOB_DONT_CARE, GLOB_DONT_CARE, profile));
  return instance;
}

OGLShaderPreprocessor::OGLShaderPreprocessor(const core::Version &ver)
    : version_(std::move(ver)) {}

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
  for (const auto &item : definitions_) {
    into << "#define " << item.first << " " << item.second << std::endl;
  }
}

}  // namespace sway::gapi
