#ifndef SWAY_GAPI_GL_OGLUNIFORM_HPP
#define SWAY_GAPI_GL_OGLUNIFORM_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/uniforms/oglintuniform.hpp>
#include <sway/gapi/gl/uniforms/oglmatuniform.hpp>
#include <sway/gapi/gl/uniforms/oglvecuniform.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramhelper.hpp>

#include <string>
#include <unordered_map>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

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
   * \~russian @brief Конструктор класса.
   *                  Выполняет инициализацию нового экземпляра класса.
   */
  OGLUniform(std::optional<u32_t> programId, const std::string &name) {
    // glGetActiveUniform
    auto location = helper_.getUniformLocation(programId.value(), name.c_str());
  }

  DTOR_VIRTUAL_DEFAULT(OGLUniform);

#pragma endregion

private:
  OGLShaderProgramHelper helper_;
  // std::unordered_map<std::string, Uniform *> uniforms_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLUNIFORM_HPP
