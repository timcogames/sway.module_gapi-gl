#ifndef SWAY_GAPI_GL_BUFFEROBJECT_H
#define SWAY_GAPI_GL_BUFFEROBJECT_H

#include <sway/gapi/gl/resource.h>
#include <sway/gapi/gl/bufferdescription.h>
#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/*!
 * \brief
 *    Представление аппаратного буфера.
 */
class BufferObject final : public Resource {
public:
#pragma region "Преобразование внутренних типов к GLenum"

	static GLenum targetToGLenum(u32_t target);

	static GLenum usageToGLenum(u32_t usage);

	static GLenum accessToGLenum(u32_t access);

#pragma endregion

	static BufferObject * create(const BufferCreateInfo & info);

	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	BufferObject(const BufferDescription & desc);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	virtual ~BufferObject();

	/*!
	 * \brief
	 *    Устанавливает данные в аппаратный буфер.
	 * 
	 * \param[in] data
	 *    Первоначальный данные.
	 */
	bool allocate(const void * data);

	/*!
	 * \brief
	 *    Изменяет данные в уже существующем буфере.
	 * 
	 * \param[in] offset
	 *    Начало изменяемого блока данных.
	 * 
	 * \param[in] size
	 *    Размер изменяемого блока данных.
	 * 
	 * \param[in] source
	 *    Область памяти, содержащая новые значения.
	 * 
	 * \sa
	 *    updateSubdata(const void *)
	 */
	void updateSubdata(u32_t offset, u32_t size, const void * source);

	/*!
	 * \brief
	 *    Изменяет данные в уже существующем буфере.
	 * 
	 * \param[in] source
	 *    Область памяти, содержащая новые значения.
	 * 
	 * \sa
	 *    updateSubdata(u32_t, u32_t, const void *)
	 */
	void updateSubdata(const void * source);

	void * map();

	void unmap();

	/*!
	 * \brief
	 *    Делает буфер текущим.
	 * 
	 * \sa
	 *    unbind()
	 */
	void bind();

	/*!
	 * \brief
	 *    Делает текущим пустой буфер.
	 * 
	 * \sa
	 *    bind()
	 */
	void unbind();

	/*!
	 * \brief
	 *    Получает выделенный размер данных.
	 */
	u32_t getAllocedSize() const;

	/*!
	 * \brief
	 *    Устанавливает целевой тип буфера.
	 * 
	 * \param[in] target
	 *    Целевой тип буфера.
	 */
	void setTarget(u32_t target);

	/*!
	 * \brief
	 *    Получает целевой тип буфера.
	 */
	u32_t getTarget() const;

	/*!
	 * \brief
	 *    Устанавливает режим работы с данными.
	 * 
	 * \param[in] usage
	 *    Режим работы.
	 */
	void setUsage(u32_t usage);
	
	/*!
	* \brief
	*    Получает режим работы с данными.
	*/
	u32_t getUsage() const;

	/*!
	 * \brief
	 *    Устанавливает количество элементов в массиве.
	 * 
	 * \param[in] capacity
	 *    Количество элементов в массиве.
	 */
	void setCapacity(s32_t capacity);

	/*!
	 * \brief
	 *    Получает количество элементов в массиве.
	 */
	s32_t getCapacity() const;

	/*!
	 * \brief
	 *    Устанавливает размер структуры данных.
	 * 
	 * \param[in] byteStride
	 *    Размер структуры.
	 */
	void setByteStride(s32_t byteStride);
	
	/*!
	 * \brief
	 *    Получает размер структуры данных.
	 */
	s32_t getByteStride() const;

	/*!
	 * \brief
	 *    Устанавливает тип данных.
	 * 
	 * \param[in] type
	 *    Тип данных.
	 */
	void setDataType(u32_t type);
	
	/*!
	 * \brief
	 *    Получает тип данных.
	 * 
	 * \return
	 *    Тип данных.
	 */
	u32_t getDataType() const;

private:
	s32_t _allocedSize;
	u32_t _target;
	u32_t _usage;
	s32_t _capacity;
	s32_t _byteStride;
	u32_t _datatype;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_BUFFEROBJECT_H
