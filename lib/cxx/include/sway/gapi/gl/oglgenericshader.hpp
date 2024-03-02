#ifndef SWAY_GAPI_GL_OGLGENERICSHADER_HPP
#define SWAY_GAPI_GL_OGLGENERICSHADER_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglgenericshaderhelper.hpp>

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

  static auto createInstance(const ShaderCreateInfo &createInfo) -> ShaderPtr_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] type Тип создаваемого шейдера.
   */
  OGLGenericShader(ShaderType type);

  OGLGenericShader(OGLGenericShaderHelperIface &helper, ShaderType type);

  /**
   * @brief Деструктор класса.
   *        Освобождает захваченные ресурсы.
   */
  virtual ~OGLGenericShader();

  /**
   * @brief Получает тип шейдера.
   *
   * @return Тип шейдера.
   */
  // clang-format off
  MTHD_OVERRIDE(auto getType() const -> ShaderType) {  // clang-format on
    return type_;
  }

  /**
   * @brief Получает ссылку на идентификатор атрибута.
   *
   * @param[in] name Имя атрибута в вершинном шейдере.
   * @return Идентификатор атрибута.
   */
  // clang-format off
  MTHD_OVERRIDE(auto getAttribLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t);  // clang-format on

  /**
   * @brief Выполняет компиляцию шейдерного объекта.
   *
   * @param[in] src Исходный код шейдера.
   */
  MTHD_OVERRIDE(void compile(lpcstr_t src));

  /**
   * @brief Возвращает статус компиляции.
   *
   * @return Если компиляция прошла успешно 'true', иначе 'false'.
   */
  // clang-format off
  MTHD_OVERRIDE(auto isCompiled() const -> bool) {  // clang-format on
    return compiled_;
  }

private:
  OGLGenericShaderHelperIface *helper_;
  ShaderType type_;  // Тип шейдера.
  bool compiled_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLGENERICSHADER_HPP
