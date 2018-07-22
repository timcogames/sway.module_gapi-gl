#ifndef SWAY_GAPI_GL_VERTEXLAYOUT_H
#define SWAY_GAPI_GL_VERTEXLAYOUT_H

#include <sway/gapi/vertexlayoutbase.h>

#include <sway/gapi/gl/shaderprogram.h>
#include <sway/gapi/gl/typeutils.h>
#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class VertexLayout : public IVertexLayoutBase {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] shader
	 *    Указатель на шейдерную программу.
	 */
	VertexLayout(IShaderProgramBase * shader);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	virtual ~VertexLayout();

	/*!
	 * \brief
	 *    Добавляет вершинный атрибут.
	 */
	virtual void addAttribute(VertexAttributeDescriptor attribute);

	virtual void enable();

	virtual void disable();

private:
	IShaderProgramBase * _shaderProgram; /*!> Шейдерная программа. */
	VertexAttribDescUmap_t _attributes;
	u32_t _attributeOffset;
	int _maxVertexAttributes; /*!< Максимальное количество атрибутов. */
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_VERTEXLAYOUT_H
