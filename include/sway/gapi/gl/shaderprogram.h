#ifndef SWAY_GAPI_GL_SHADERPROGRAM_H
#define SWAY_GAPI_GL_SHADERPROGRAM_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/*!
 * \brief
 *    Представление шейдерной программы.
 */
class ShaderProgram final : public IShaderProgramBase {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderProgram();

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	virtual ~ShaderProgram();

	/*!
	 * \brief
	 *    Связывает шейдерный объект с программным объектом.
	 * 
	 * \param[in] shader
	 *    Указатель на связываемый шейдерный объект.
	 * 
	 * \sa
	 *    detach(u32_t)
	 */
	virtual void attach(IShaderBase * shader);

	/*!
	 * \brief
	 *    Отсоединяет шейдерный объект от программного объекта.
	 * 
	 * \param[in] objectId
	 *    Отвязываемый шейдерный объект.
	 * 
	 * \sa
	 *    attach(IShaderBase *)
	 */
	virtual void detach(u32_t objectId);
	
	/*!
	 * \brief
	 *    Компонует программный объект.
	 * 
	 * \sa
	 *    isLinked() const
	 */
	virtual void link();

	/*!
	 * \brief
	 *    Возвращает статус компоновки.
	 * 
	 * \sa
	 *    link()
	 */
	virtual bool isLinked() const;
	
	/*!
	 * \brief
	 *    Проверяет скомпоновонный объект на корректность.
	 * 
	 * \sa
	 *    isValidated() const
	 */
	virtual void validate();

	/*!
	 * \brief
	 *    Возвращает статус корректности скомпоновоного объекта.
	 * 
	 * \sa
	 *    validate()
	 */
	virtual bool isValidated() const;

	/*!
	 * \brief
	 *    Делает шейдерную программу активной.
	 * 
	 * \sa
	 *    unuse()
	 *    isUsed() const
	 */
	virtual void use();

	/*!
	 * \brief
	 *    Деактивирует шейдерную программу.
	 * 
	 * \sa
	 *    use()
	 *    isUsed() const
	 */
	virtual void unuse();

	/*!
	 * \brief
	 *    Возвращает логическое значение, которое определяет,
	 *    является ли шейдерная программа активной в текущем состоянии рендеринга.
	 * 
	 * \sa
	 *    use()
	 *    unuse()
	 */
	virtual bool isUsed() const;

	/*!
	 * \brief
	 *    Передает значение uniform-переменной в шейдер.
	 * 
	 * \param[in] uniform
	 *    Имя uniform-переменной.
	 * 
	 * \param[in] vec
	 *    Значение uniform-переменной.
	 */
	virtual void setUniformVec4f(const std::string & uniform, const math::vec4f_t & vec);
	
	/*!
	 * \brief
	 *    Передает значение uniform-переменной в шейдер.
	 * 
	 * \param[in] uniform
	 *    Имя uniform-переменной.
	 * 
	 * \param[in] col
	 *    Значение uniform-переменной.
	 */
	virtual void setUniformCol4f(const std::string & uniform, const math::col4f_t & col);

	/*!
	 * \brief
	 *    Получает идентификатор объекта.
	 */
	virtual u32_t getObjectId() const;

private:
	std::set<u32_t> _shaderIdSet;
	UniformVec4fUmap_t _uniformVec4fSet;
	bool _linked;
	bool _validated;
	u32_t _objectId;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_SHADERPROGRAM_H