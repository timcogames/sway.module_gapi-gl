#ifndef SWAY_GAPI_GL_OGLUNIFORM_HPP
#define SWAY_GAPI_GL_OGLUNIFORM_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/uniforms/oglintuniform.hpp>
#include <sway/gapi/gl/uniforms/oglmatuniform.hpp>
#include <sway/gapi/gl/uniforms/oglvecuniform.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramhelper.hpp>

#include <string>
#include <unordered_map>

namespace sway::gapi {

struct UniformStack {};

using UniformStackPtr_t = struct UniformStack *;

class OGLUniform final : public UniformStack {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance(std::optional<u32_t> programId, const std::string &name) -> UniformStackPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  /**
   * @brief \~english Constructor class. Performs initialization of a new instance of the class. \~russian Конструктор
   * класса. Выполняет инициализацию нового экземпляра класса.
   */
  OGLUniform(std::optional<u32_t> programId, const std::string &name) {
    // glGetActiveUniform
    auto location = helper_.getUniformLocation(programId.value(), name.c_str());
  }

  virtual ~OGLUniform() = default;

#pragma endregion

private:
  OGLShaderProgramHelper helper_;
  // std::unordered_map<std::string, Uniform *> uniforms_;
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_OGLUNIFORM_HPP
