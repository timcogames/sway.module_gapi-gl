#ifndef SWAY_GAPI_VERTEXLAYOUT_H
#define SWAY_GAPI_VERTEXLAYOUT_H

#include <sway/gapi/shaderprogram.h>
#include <sway/gapi/vertexsemantics.h>
#include <sway/gapi/vertexattribute.h>
#include <sway/gapi/typeutils.h>
#include <sway/gapi/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class VertexLayout {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] type
	 *    Указатель на шейдерную программу.
	 */
	VertexLayout(ShaderProgram * program);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	~VertexLayout();

	void addAttribute(VertexSemantic_t semantic, Type_t format, s32_t numComponents);

	void enable();

	void disable();

	void setAttributes(VertexAttributeUmap_t attributes);

	VertexAttributeUmap_t getAttributes();

	void setMaxVertexAttributes(int value);

	/*!
	 * \brief
	 *    Возвращает максимальное количество допустимых атрибутов.
	 */
	int getMaxVertexAttributes();

private:
	ShaderProgram * _program; /*!> Шейдерная программа. */
	VertexAttributeUmap_t _attributes;
	u32_t _attributeOffset;
	int _maxVertexAttributes; /*!< Максимальное количество атрибутов. */
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_VERTEXLAYOUT_H