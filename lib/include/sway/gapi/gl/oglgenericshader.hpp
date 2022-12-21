#ifndef SWAY_GAPI_GL_OGLGENERICSHADER_HPP
#define SWAY_GAPI_GL_OGLGENERICSHADER_HPP

#include <sway/gapi/gl/oglgenericshaderhelper.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/**
 * @brief Представление шейдерного объекта.
 */
class OGLGenericShader final : public Shader {
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
  OGLGenericShader(ShaderType type);

  /**
   * @brief Деструктор класса.
   *        Освобождает захваченные ресурсы.
   */
  virtual ~OGLGenericShader();

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
  OGLGenericShaderHelper helper_;
  ShaderType type_;  // Тип шейдера.
  bool compiled_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLGENERICSHADER_HPP
