#ifndef SWAY_GAPI_GL_OGLSHADERPREPROCESSOR_HPP
#define SWAY_GAPI_GL_OGLSHADERPREPROCESSOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <map>
#include <ostream>  // std::ostream
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class ShaderSource {
public:
  inline static std::string WHITESPACE{" "};
  inline static std::string TABULATION = WHITESPACE + WHITESPACE;

  void addVersion(const core::Version &version) {
    source_ << "#version" << WHITESPACE << version.getMajor();
    auto profile = version.getExtra();
    if (!profile.empty()) {
      source_ << WHITESPACE << profile;
    }

    source_ << std::endl << std::endl;
  }

  void addDefaultPrecision() {
    source_ << "#ifdef GL_FRAGMENT_PRECISION_HIGH" << std::endl;
    source_ << TABULATION << "precision" << WHITESPACE << PrecisionQualifier::HI << WHITESPACE << "float;" << std::endl;
    source_ << "#else" << std::endl;
    source_ << TABULATION << "precision" << WHITESPACE << PrecisionQualifier::MD << WHITESPACE << "float;" << std::endl;
    source_ << "#endif" << std::endl;
  }

  auto toStr() const -> std::string { return source_.str(); }

private:
  std::stringstream source_;
};

class OGLShaderPreprocessor : public ShaderPreprocessor {
public:
  using CompilerDefinitionContainer_t = std::map<std::string, std::string>;
  using ParameterContainer_t = std::map<std::string, std::string>;

#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance(u32_t major, lpcstr_t profile) -> ShaderPreprocessor::Ptr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  OGLShaderPreprocessor(const core::Version &version);

  DTOR_VIRTUAL_DEFAULT(OGLShaderPreprocessor);

#pragma endregion

#pragma region "Overridden ShaderPreprocessor methods"

  MTHD_OVERRIDE(void addDefine(const std::string &name, const std::string &val = std::string()));

  MTHD_OVERRIDE(auto hasDefined(const std::string &name) const -> bool);

#pragma endregion

  void evaluate(std::ostream &into);

  auto getVersion() const -> core::Version { return version_; }

private:
  core::Version version_;
  CompilerDefinitionContainer_t definitions_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLSHADERPREPROCESSOR_HPP
