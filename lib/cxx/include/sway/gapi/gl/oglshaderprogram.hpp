#ifndef SWAY_GAPI_GL_OGLSHADERPROGRAM_HPP
#define SWAY_GAPI_GL_OGLSHADERPROGRAM_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramhelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

/**
 * \~russian @brief Представление шейдерной программы.
 */
class OGLShaderProgram final : public ShaderProgram {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance() -> ShaderProgramPtr_t;

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
  OGLShaderProgram();

  DTOR_VIRTUAL(OGLShaderProgram);

#pragma endregion

#pragma region "Overridden ShaderProgram methods"

  /**
   * \~russian @brief Связывает шейдерный объект с программным объектом.
   *
   * @param[in] shader Указатель на связываемый шейдерный объект.
   * @sa detach(std::pair<ShaderType::Enum, ShaderPtr_t>)
   */
  MTHD_OVERRIDE(void attach(ShaderPtr_t shader));

  /**
   * \~russian @brief Отсоединяет шейдерный объект от программного объекта.
   *
   * @param[in] objectId Указатель на отвязываемый шейдерный объект.
   * @sa attach(ShaderPtr_t)
   */
  MTHD_OVERRIDE(void detach(std::pair<ShaderType::Enum, ShaderPtr_t> pair, bool erasing));

  MTHD_OVERRIDE(auto getShader(ShaderType::Enum type) -> ShaderPtr_t);

  /**
   * \~russian @brief Компонует программный объект.
   *
   * @sa isLinked() const
   */
  MTHD_OVERRIDE(void link());

  /**
   * \~russian @brief Возвращает статус компоновки.
   *
   * @sa link()
   */
  MTHD_OVERRIDE(auto isLinked() const -> bool) {
    return linked_;
  }

  /**
   * \~russian @brief Проверяет скомпоновонный объект на корректность.
   *
   * @sa isValidated() const
   */
  MTHD_OVERRIDE(void validate());

  /**
   * \~russian @brief Возвращает статус корректности скомпоновоного объекта.
   *
   * @sa validate()
   */
  MTHD_OVERRIDE(auto isValidated() const -> bool) {
    return validated_;
  }

  /**
   * \~russian @brief Делает шейдерную программу активной.
   *
   * @sa unuse(),
   *     isUsed() const
   */
  MTHD_OVERRIDE(void use());

  /**
   * \~russian @brief Деактивирует шейдерную программу.
   *
   * @sa use(),
   *     isUsed() const
   */
  MTHD_OVERRIDE(void unuse());

  /**
   * \~russian @brief Возвращает логическое значение, которое определяет,
   *                  является ли шейдерная программа активной в текущем состоянии рендеринга.
   *
   * @sa use(),
   *     unuse()
   */
  MTHD_OVERRIDE(auto isUsed() const -> bool);

  /**
   * \~russian @brief Передает значение uniform-переменной в шейдер.
   *
   * @param[in] uniform Имя uniform-переменной.
   * @param[in] vec Значение uniform-переменной.
   */
  MTHD_OVERRIDE(void setUniformVec4f(const std::string &uniform, const math::vec4f_t &vec));

  /**
   * \~russian @brief Передает значение uniform-переменной в шейдер.
   *
   * @param[in] uniform Имя uniform-переменной.
   * @param[in] col Значение uniform-переменной.
   */
  MTHD_OVERRIDE(void setUniformCol4f(const std::string &uniform, const math::col4f_t &col));

  MTHD_OVERRIDE(void setUniformMat4f(const std::string &uniform, const math::mat4f_t &mat));

  MTHD_OVERRIDE(void setUniform1i(const std::string &uniform, i32_t val));

  MTHD_OVERRIDE(void setUniform1f(const std::string &uniform, f32_t val));

#pragma endregion

private:
  OGLShaderProgramHelper *helper_;
  std::map<ShaderType::Enum, ShaderPtr_t> shaders_;
  UniformVec4fUmap_t uniformVec4fSet_;
  UniformMat4fUmap_t uniformMat4fSet_;
  Uniform1iUmap_t uniform1iSet_;
  Uniform1fUmap_t uniform1fSet_;
  bool linked_;
  bool validated_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLSHADERPROGRAM_HPP
