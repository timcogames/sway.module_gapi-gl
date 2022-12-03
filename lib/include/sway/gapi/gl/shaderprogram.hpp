#ifndef SWAY_GAPI_GL_SHADERPROGRAM_HPP
#define SWAY_GAPI_GL_SHADERPROGRAM_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/**
 * @brief Представление шейдерной программы.
 */
class ShaderProgram final : public AShaderProgramBase {
public:
  static auto createInstance() -> ShaderProgramRef_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  ShaderProgram();

  /**
   * @brief Деструктор класса. Освобождает захваченные ресурсы.
   */
  virtual ~ShaderProgram();

  /**
   * @brief Связывает шейдерный объект с программным объектом.
   * @param[in] shader Указатель на связываемый шейдерный объект.
   * @sa detach(u32_t)
   */
  virtual void attach(ShaderRef_t shader);

  /**
   * @brief Отсоединяет шейдерный объект от программного объекта.
   * @param[in] attachedId Отвязываемый шейдерный объект.
   * @sa attach(ShaderRef_t)
   */
  virtual void detach(u32_t attachedId);

  /**
   * @brief Компонует программный объект.
   * @sa isLinked() const
   */
  virtual void link();

  /**
   * @brief Возвращает статус компоновки.
   * @sa link()
   */
  virtual auto isLinked() const -> bool;

  /**
   * @brief Проверяет скомпоновонный объект на корректность.
   * @sa isValidated() const
   */
  virtual void validate();

  /**
   * @brief Возвращает статус корректности скомпоновоного объекта.
   * @sa validate()
   */
  // clang-format off
  MTHD_OVERRIDE(auto isValidated() const -> bool);  // clang-format on

  /**
   * @brief Делает шейдерную программу активной.
   * @sa unuse(),
   *     isUsed() const
   */
  virtual void use();

  /**
   * @brief Деактивирует шейдерную программу.
   * @sa use(),
   *     isUsed() const
   */
  virtual void unuse();

  /**
   * @brief Возвращает логическое значение, которое определяет,
   *        является ли шейдерная программа активной в текущем состоянии рендеринга.
   * @sa use(),
   *     unuse()
   */
  // clang-format off
  MTHD_OVERRIDE(auto isUsed() const -> bool);  // clang-format on

  /**
   * @brief Передает значение uniform-переменной в шейдер.
   * @param[in] uniform Имя uniform-переменной.
   * @param[in] vec Значение uniform-переменной.
   */
  MTHD_OVERRIDE(void setUniformVec4f(const std::string &uniform, const math::vec4f_t &vec));

  /**
   * @brief Передает значение uniform-переменной в шейдер.
   * @param[in] uniform Имя uniform-переменной.
   * @param[in] col Значение uniform-переменной.
   */
  MTHD_OVERRIDE(void setUniformCol4f(const std::string &uniform, const math::col4f_t &col));

private:
  // ShaderObjectIdSet_t _objectIdSet;
  std::set<int> _objectIdSet;
  UniformVec4fUmap_t _uniformVec4fSet;
  bool _linked;
  bool _validated;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif
