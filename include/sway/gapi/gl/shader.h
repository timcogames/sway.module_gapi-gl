#ifndef SWAY_GAPI_GL_SHADER_H
#define SWAY_GAPI_GL_SHADER_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/*!
 * \brief
 *    Представление шейдерного объекта.
 */
class Shader final : public AShaderBase {
public:
#pragma region "Преобразование внутренних типов к GLenum"

	static GLenum typeToGLenum(ShaderType_t type);

#pragma endregion

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] type
	 *    Тип создаваемого шейдера.
	 */
	Shader(ShaderType_t type);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *    Освобождает захваченные ресурсы.
	 */
	virtual ~Shader();

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

private:
	ShaderType_t _type; /*!< Тип шейдера. */
	bool _compiled;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_SHADER_H
