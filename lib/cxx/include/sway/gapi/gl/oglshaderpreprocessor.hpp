#ifndef SWAY_GAPI_GL_OGLSHADERPREPROCESSOR_HPP
#define SWAY_GAPI_GL_OGLSHADERPREPROCESSOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <map>
#include <ostream>  // std::ostream
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLShaderPreprocessor {
public:
  using CompilerDefinitionContainer_t = std::map<std::string, std::string>;
  using ParameterContainer_t = std::map<std::string, std::string>;

  OGLShaderPreprocessor(ShaderType type, const core::Version &version);

  ~OGLShaderPreprocessor() = default;

  void addDefine(const std::string &name, const std::string &val = std::string());

  auto hasDefined(const std::string &name) const -> bool;

  void evaluate(std::ostream &into);

private:
  ShaderType type_;
  core::Version version_;
  CompilerDefinitionContainer_t definitions_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSHADERPREPROCESSOR_HPP
