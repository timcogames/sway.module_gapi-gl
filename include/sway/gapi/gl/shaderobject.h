#ifndef SWAY_GAPI_GL_SHADEROBJECT_H
#define SWAY_GAPI_GL_SHADEROBJECT_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/*!
 * \brief
 *    Представление шейдерного объекта.
 */
class ShaderObject final : public IShaderBase {
public:
#pragma region "Преобразование внутренних типов к GLenum или строке"

	static GLenum typeToGLenum(ShaderType_t type);

	static std::string typeToStr(ShaderType_t type);

#pragma endregion

	static ShaderObject * create(const ShaderCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] type
	 *    Тип создаваемого шейдера.
	 */
	ShaderObject(ShaderType_t type);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	virtual ~ShaderObject();

	/*!
	 * \brief
	 *    Выполняет компиляцию шейдерного объекта.
	 * 
	 * \param[in] source
	 *    Исходный код шейдера.
	 */
	virtual void compile(lpcstr_t source);

	/*!
	 * \brief
	 *    Возвращает статус компиляции.
	 * 
	 * \return
	 *    Если компиляция прошла успешно 'true', иначе 'false'.
	 */
	virtual bool isCompiled() const;

	/*!
	 * \brief
	 *    Получает тип шейдера.
	 * 
	 * \return
	 *    Тип шейдера.
	 */
	virtual ShaderType_t getType() const;

	/*!
	 * \brief
	 *    Получает идентификатор объекта.
	 */
	virtual u32_t getObjectId() const;

private:
	ShaderType_t _type; /*!< Тип шейдера. */
	bool _compiled;
	u32_t _objectId;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_SHADEROBJECT_H
