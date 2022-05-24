#ifndef SWAY_GAPI_GL_VERTEXLAYOUT_HPP
#define SWAY_GAPI_GL_VERTEXLAYOUT_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/shaderprogram.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class VertexLayout : public IVertexLayoutBase {
public:
  static VertexLayoutRef_t createInstance(ShaderProgramRef_t program);

  /*!
   * \brief
   *    Конструктор класса.
   *    Выполняет инициализацию нового экземпляра класса.
   *
   * \param[in] program
   *    Указатель на шейдерную программу.
   */
  VertexLayout(ShaderProgramRef_t program);

  /*!
   * \brief
   *    Деструктор класса.
   *    Освобождает захваченные ресурсы.
   */
  virtual ~VertexLayout();

  /*!
   * \brief
   *    Добавляет вершинный атрибут.
   *
   * \param[in] desc
   *    Описание вершинного атрибута.
   */
  virtual void addAttribute(VertexAttributeDescriptor desc);

  /*!
   * \brief
   *    Включает чтение атрибутов.
   */
  virtual void enable();

  /*!
   * \brief
   *    Отключает чтение атрибутов.
   */
  virtual void disable();

private:
  ShaderProgramRef_t _shaderProgram; /*!> Шейдерная программа. */
  VertexAttribDescUmap_t _attributes;
  u32_t _attributeOffset;
  int _maxVertexAttributes; /*!< Максимальное количество атрибутов. */
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif
