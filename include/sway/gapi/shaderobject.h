#ifndef SWAY_GAPI_SHADEROBJECT_H
#define SWAY_GAPI_SHADEROBJECT_H

#include <sway/gapi/resource.h>
#include <sway/gapi/shaderobjectcreateinfo.h>
#include <sway/gapi/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/*!
 * \brief
 *    Представление шейдерного объекта.
 */
class ShaderObject final : public Resource {
public:
#pragma region "Преобразование внутренних типов к GLenum или строке"

	static GLenum typeToGLenum(u32_t type);

	static std::string typeToStr(u32_t type);

#pragma endregion

	static ShaderObject * create(const ShaderObjectCreateInfo & createInfo);

	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] type
	 *    Тип создаваемого шейдера.
	 */
	ShaderObject(u32_t type);

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
	void compile(lpcstr_t source);

	/*!
	 * \brief
	 *    Возвращает статус компиляции.
	 * 
	 * \return
	 *    Если компиляция прошла успешно 'true', иначе 'false'.
	 */
	bool isCompiled() const;

	/*!
	 * \brief
	 *    Получает тип шейдера.
	 * 
	 * \return
	 *    Тип шейдера.
	 */
	u32_t getType() const;

private:
	u32_t _type; /*!< Тип шейдера. */
	bool _compiled;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_SHADEROBJECT_H
