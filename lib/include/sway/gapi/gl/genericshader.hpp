#ifndef SWAY_GAPI_GL_GENERICSHADER_HPP
#define SWAY_GAPI_GL_GENERICSHADER_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/shaderhelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/**
 * @brief Представление шейдерного объекта.
 */
class GenericShader final : public Shader {
public:
#pragma region "Преобразование внутренних типов к GLenum"

  static auto typeToGLenum(ShaderType type) -> GLenum;

#pragma endregion

  static auto createInstance(const ShaderCreateInfo &createInfo) -> ShaderRef_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] type Тип создаваемого шейдера.
   */
  GenericShader(ShaderType type);

  /**
   * @brief Деструктор класса.
   *        Освобождает захваченные ресурсы.
   */
  virtual ~GenericShader();

  /**
   * @brief Выполняет компиляцию шейдерного объекта.
   *
   * @param[in] source Исходный код шейдера.
   */
  MTHD_OVERRIDE(void compile(lpcstr_t source));

  /**
   * @brief Возвращает статус компиляции.
   *
   * @return Если компиляция прошла успешно 'true', иначе 'false'.
   */
  // clang-format off
  MTHD_OVERRIDE(auto isCompiled() const -> bool) {  // clang-format on
    return compiled_;
  }

  /**
   * @brief Получает тип шейдера.
   *
   * @return Тип шейдера.
   */
  // clang-format off
  MTHD_OVERRIDE(auto getType() const -> ShaderType) {  // clang-format on
    return type_;
  }

private:
  ShaderHelper shaderHelper_;
  ShaderType type_;  // Тип шейдера.
  bool compiled_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_GENERICSHADER_HPP
