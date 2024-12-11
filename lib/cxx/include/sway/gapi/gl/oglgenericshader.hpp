#ifndef SWAY_GAPI_GL_OGLGENERICSHADER_HPP
#define SWAY_GAPI_GL_OGLGENERICSHADER_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglgenericshaderhelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

/**
 * \~russian @brief Представление шейдерного объекта.
 */
class OGLGenericShader final : public Shader {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance(const ShaderCreateInfo &createInfo) -> ShaderPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  /**
   * \~russian @brief Конструктор класса.
   *                  Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] type Тип создаваемого шейдера.
   */
  OGLGenericShader(ShaderType::Enum type);

  OGLGenericShader(OGLGenericShaderHelperIface &helper, ShaderType::Enum type);

  DTOR_VIRTUAL(OGLGenericShader);

#pragma endregion

#pragma region "Overridden Shader methods"

  /**
   * \~russian @brief Получает тип шейдера.
   *
   * @return Тип шейдера.
   */
  MTHD_OVERRIDE(auto getType() const -> ShaderType::Enum) {
    return type_;
  }

  /**
   * \~russian @brief Получает ссылку на идентификатор атрибута.
   *
   * @param[in] name Имя атрибута в вершинном шейдере.
   * @return Идентификатор атрибута.
   */
  MTHD_OVERRIDE(auto getAttribLocation(std::optional<u32_t> progId, lpcstr_t name) -> i32_t);

  /**
   * \~russian @brief Выполняет компиляцию шейдерного объекта.
   *
   * @param[in] src Исходный код шейдера.
   */
  MTHD_OVERRIDE(void compile(lpcstr_t src));

  /**
   * \~russian @brief Возвращает статус компиляции.
   *
   * @return Если компиляция прошла успешно 'true', иначе 'false'.
   */
  MTHD_OVERRIDE(auto isCompiled() const -> bool) {
    return compiled_;
  }

#pragma endregion

private:
  OGLGenericShaderHelperIface *helper_;
  ShaderType::Enum type_;  // Тип шейдера.
  bool compiled_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLGENERICSHADER_HPP
