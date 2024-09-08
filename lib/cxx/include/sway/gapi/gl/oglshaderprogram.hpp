#ifndef SWAY_GAPI_GL_OGLSHADERPROGRAM_HPP
#define SWAY_GAPI_GL_OGLSHADERPROGRAM_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramhelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/**
 * @brief Представление шейдерной программы.
 */
class OGLShaderProgram final : public ShaderProgram {
public:
  static auto createInstance() -> ShaderProgramPtr_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  OGLShaderProgram();

  /**
   * @brief Деструктор класса.
   *        Освобождает захваченные ресурсы.
   */
  virtual ~OGLShaderProgram();

  /**
   * @brief Связывает шейдерный объект с программным объектом.
   *
   * @param[in] shader Указатель на связываемый шейдерный объект.
   * @sa detach(std::pair<ShaderType, ShaderPtr_t>)
   */
  MTHD_OVERRIDE(void attach(ShaderPtr_t shader));

  /**
   * @brief Отсоединяет шейдерный объект от программного объекта.
   *
   * @param[in] objectId Указатель на отвязываемый шейдерный объект.
   * @sa attach(ShaderPtr_t)
   */
  MTHD_OVERRIDE(void detach(std::pair<ShaderType, ShaderPtr_t> pair, bool erasing));

  MTHD_OVERRIDE(auto getShader(ShaderType type) -> ShaderPtr_t);

  /**
   * @brief Компонует программный объект.
   *
   * @sa isLinked() const
   */
  MTHD_OVERRIDE(void link());

  /**
   * @brief Возвращает статус компоновки.
   *
   * @sa link()
   */
  MTHD_OVERRIDE(auto isLinked() const -> bool) {
    return linked_;
  }

  /**
   * @brief Проверяет скомпоновонный объект на корректность.
   *
   * @sa isValidated() const
   */
  MTHD_OVERRIDE(void validate());

  /**
   * @brief Возвращает статус корректности скомпоновоного объекта.
   *
   * @sa validate()
   */
  MTHD_OVERRIDE(auto isValidated() const -> bool) {
    return validated_;
  }

  /**
   * @brief Делает шейдерную программу активной.
   *
   * @sa unuse(),
   *     isUsed() const
   */
  MTHD_OVERRIDE(void use());

  /**
   * @brief Деактивирует шейдерную программу.
   *
   * @sa use(),
   *     isUsed() const
   */
  MTHD_OVERRIDE(void unuse());

  /**
   * @brief Возвращает логическое значение, которое определяет,
   *        является ли шейдерная программа активной в текущем состоянии рендеринга.
   *
   * @sa use(),
   *     unuse()
   */
  MTHD_OVERRIDE(auto isUsed() const -> bool);

  /**
   * @brief Передает значение uniform-переменной в шейдер.
   *
   * @param[in] uniform Имя uniform-переменной.
   * @param[in] vec Значение uniform-переменной.
   */
  MTHD_OVERRIDE(void setUniformVec4f(const std::string &uniform, const math::vec4f_t &vec));

  /**
   * @brief Передает значение uniform-переменной в шейдер.
   *
   * @param[in] uniform Имя uniform-переменной.
   * @param[in] col Значение uniform-переменной.
   */
  MTHD_OVERRIDE(void setUniformCol4f(const std::string &uniform, const math::col4f_t &col));

  MTHD_OVERRIDE(void setUniformMat4f(const std::string &uniform, const math::mat4f_t &mat));

  MTHD_OVERRIDE(void setUniform1i(const std::string &uniform, i32_t val));

  MTHD_OVERRIDE(void setUniform1f(const std::string &uniform, f32_t val));

private:
  OGLShaderProgramHelper *helper_;
  std::map<ShaderType, ShaderPtr_t> shaders_;
  UniformVec4fUmap_t uniformVec4fSet_;
  UniformMat4fUmap_t uniformMat4fSet_;
  Uniform1iUmap_t uniform1iSet_;
  Uniform1fUmap_t uniform1fSet_;
  bool linked_;
  bool validated_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLSHADERPROGRAM_HPP
