#include <sway/gapi/gl/oglshaderpreprocessor.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLShaderPreprocessor::createInstance(u32_t major, lpcstr_t profile) -> ShaderPreprocessor::Ptr_t {
  auto instance = new OGLShaderPreprocessor(core::Version(major, DONT_CARE, DONT_CARE, profile));
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

NS_END()  // namespace gapi
NS_END()  // namespace sway
