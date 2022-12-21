#ifndef SWAY_GAPI_GL_OGLVERTEXATTRIBLAYOUT_HPP
#define SWAY_GAPI_GL_OGLVERTEXATTRIBLAYOUT_HPP

#include <sway/gapi/gl/oglgenericshaderhelper.hpp>
#include <sway/gapi/gl/oglshaderprogram.hpp>
#include <sway/gapi/gl/oglvertexattriblayouthelper.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLVertexAttribLayout final : public VertexAttribLayout {
public:
  static auto createInstance(ShaderProgramRef_t program) -> VertexAttribLayoutPtr_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] program Указатель на шейдерную программу.
   */
  OGLVertexAttribLayout(ShaderProgramRef_t program);

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
  MTHD_OVERRIDE(void addAttribute(VertexAttributeDescriptor desc));

  /**
   * @brief Включает чтение атрибутов.
   */
  MTHD_OVERRIDE(void enable());

  /**
   * @brief Отключает чтение атрибутов.
   */
  MTHD_OVERRIDE(void disable());

private:
  OGLGenericShaderHelper shaderHelper_;
  OGLVertexAttribLayoutHelper helper_;
  ShaderProgramRef_t shaderProgram_;  // Шейдерная программа.
  VertexAttribDescUmap_t attributes_;
  u32_t attributeOffset_;
  int maxVertexAttributes_;  // Максимальное количество атрибутов.
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLVERTEXATTRIBLAYOUT_HPP
