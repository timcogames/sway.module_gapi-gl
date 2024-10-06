#ifndef SWAY_GAPI_GL_OGLVERTEXATTRIBLAYOUT_HPP
#define SWAY_GAPI_GL_OGLVERTEXATTRIBLAYOUT_HPP

#include <sway/gapi/gl/oglshaderprogram.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/oglvertexattriblayouthelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLVertexAttribLayout final : public VertexAttribLayout {
public:
  static auto createInstance(ShaderProgramPtr_t program) -> VertexAttribLayoutPtr_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] progId Идентификатор шейдерной программы.
   */
  OGLVertexAttribLayout(ShaderProgramPtr_t program);

  /**
   * @brief Деструктор класса.
   *        Освобождает захваченные ресурсы.
   */
  virtual ~OGLVertexAttribLayout();

  /**
   * @brief Добавляет вершинный атрибут.
   *
   * @param[in] desc Описание вершинного атрибута.
   */
  MTHD_OVERRIDE(void addAttribute(VertexAttribDescriptor desc));

  /**
   * @brief Включает чтение атрибутов.
   */
  MTHD_OVERRIDE(void enable());

  /**
   * @brief Отключает чтение атрибутов.
   */
  MTHD_OVERRIDE(void disable());

private:
  OGLVertexAttribLayoutHelper helper_;
  ShaderProgramPtr_t program_;
  VertexAttribDescUmap_t attribs_;
  u32_t attribOffset_;
  int maxVertexAttribs_;  // Максимальное количество атрибутов.
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLVERTEXATTRIBLAYOUT_HPP
