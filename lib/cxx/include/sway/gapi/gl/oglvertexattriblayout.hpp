#ifndef SWAY_GAPI_GL_OGLVERTEXATTRIBLAYOUT_HPP
#define SWAY_GAPI_GL_OGLVERTEXATTRIBLAYOUT_HPP

#include <sway/gapi/gl/oglshaderprogram.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/oglvertexattriblayouthelper.hpp>

namespace sway::gapi {

class OGLVertexAttribLayout final : public VertexAttribLayout {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance(typedefs::ShaderProgramPtr_t program) -> typedefs::VertexAttribLayoutPtr_t;

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
   * @param[in] progId Идентификатор шейдерной программы.
   */
  OGLVertexAttribLayout(typedefs::ShaderProgramPtr_t program);

  DTOR_VIRTUAL(OGLVertexAttribLayout);

#pragma endregion

  /**
   * \~russian @brief Добавляет вершинный атрибут.
   *
   * @param[in] desc Описание вершинного атрибута.
   */
  MTHD_OVERRIDE(void addAttribute(VertexAttribDescriptor desc));

  /**
   * \~russian @brief Включает чтение атрибутов.
   */
  MTHD_OVERRIDE(void enable());

  /**
   * \~russian @brief Отключает чтение атрибутов.
   */
  MTHD_OVERRIDE(void disable());

private:
  OGLVertexAttribLayoutHelper helper_;
  typedefs::ShaderProgramPtr_t program_;
  VertexAttribDescUmap_t attribs_;
  u32_t attribOffset_;
  int maxVertexAttribs_;  // Максимальное количество атрибутов.
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_OGLVERTEXATTRIBLAYOUT_HPP
