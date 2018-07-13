#ifndef SWAY_GAPI_SHADERPROGRAM_H
#define SWAY_GAPI_SHADERPROGRAM_H

#include <sway/gapi/shaderobject.h>
#include <sway/gapi/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/*!
 * \brief
 *    Представление шейдерной программы.
 */
class ShaderProgram final : public Resource {
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
	 *    detach(ResourceId_t)
	 */
	void attach(ShaderObject * shader);

	/*!
	 * \brief
	 *    Отсоединяет шейдерный объект от программного объекта.
	 * 
	 * \param[in] handle
	 *    Отвязываемый шейдерный объект.
	 * 
	 * \sa
	 *    attach(ShaderObject *)
	 */
	void detach(ResourceId_t handle);
	
	/*!
	 * \brief
	 *    Компоновка шей­дерных объектов.
	 */
	void link();

	/*!
	 * \brief
	 *    Возвращает статус компоновки.
	 * 
	 * \return
	 *    Если компоновка прошла успешно 'true', иначе 'false'.
	 */
	bool isLinked() const;
	
	/*!
	 * \brief
	 *    Проверяет программный объект.
	 */
	void validate();

	bool isValidated() const;

	void use();

	void unuse();

	bool isUsed() const;

	void setUniformVec4f(const std::string & uniform, const math::vec4f_t & vec);
	
	void setUniformCol4f(const std::string & uniform, const math::col4f_t & col);

private:
	ResourceIdSet_t _shaderSet;
	UniformVec4fUmap_t _uniformVec4fSet;
	bool _linked;
	bool _validated;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_SHADERPROGRAM_H
