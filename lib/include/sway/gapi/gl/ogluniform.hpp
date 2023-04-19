#ifndef SWAY_GAPI_GL_OGLUNIFORM_HPP
#define SWAY_GAPI_GL_OGLUNIFORM_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/uniforms/oglintuniform.hpp>
#include <sway/gapi/gl/uniforms/oglmatuniform.hpp>
#include <sway/gapi/gl/uniforms/oglvecuniform.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramhelper.hpp>

#include <string>
#include <unordered_map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class UniformStack {
public:
};

class OGLUniform final : public UniformStack {
public:
  static auto createInstance(std::optional<u32_t> programId, const std::string &name) -> std::shared_ptr<UniformStack>;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  OGLUniform(std::optional<u32_t> programId, const std::string &name) {
    // glGetActiveUniform
    auto location = helper_.getUniformLocation(programId.value(), name.c_str());
  }

  /**
   * @brief Деструктор класса.
   *        Освобождает захваченные ресурсы.
   */
  virtual ~OGLUniform() = default;

private:
  OGLShaderProgramHelper helper_;
  // std::unordered_map<std::string, Uniform *> uniforms_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLUNIFORM_HPP
