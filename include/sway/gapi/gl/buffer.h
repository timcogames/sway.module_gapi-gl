#ifndef SWAY_GAPI_GL_BUFFER_H
#define SWAY_GAPI_GL_BUFFER_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/*!
 * \brief
 *    Представление аппаратного буфера.
 */
class Buffer final : public ABufferBase {
public:
#pragma region "Преобразование внутренних типов к GLenum"

	static GLenum targetToGLenum(BufferTarget_t target);

	static GLenum usageToGLenum(BufferUsage_t usage);

	static GLenum accessToGLenum(BufferAccess_t access);

#pragma endregion

	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Buffer(const BufferDescriptor & desc);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	virtual ~Buffer();

	/*!
	 * \brief
	 *    Устанавливает данные в аппаратный буфер.
	 * 
	 * \param[in] data
	 *    Первоначальный данные.
	 */
	virtual bool allocate(const void * data);

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
	virtual void updateSubdata(u32_t offset, u32_t size, const void * source);

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
	virtual void updateSubdata(const void * source);

	/*!
	 * \brief
	 *    Получает указатель на область памяти, в которой находятся данные буфера.
	 * 
	 * \sa
	 *    unmap()
	 */
	virtual void * map();

	/*!
	 * \brief
	 *    Возвращает данные буфера в память.
	 * 
	 * \sa
	 *    map()
	 */
	virtual void unmap();

	/*!
	 * \brief
	 *    Делает буфер текущим.
	 * 
	 * \sa
	 *    unbind()
	 */
	virtual void bind();

	/*!
	 * \brief
	 *    Делает текущим пустой буфер.
	 * 
	 * \sa
	 *    bind()
	 */
	virtual void unbind();

	/*!
	 * \brief
	 *    Получает выделенный размер данных.
	 */
	virtual u32_t getAllocedSize() const;

	/*!
	 * \brief
	 *    Устанавливает целевой тип буфера.
	 * 
	 * \param[in] target
	 *    Целевой тип буфера.
	 */
	virtual void setTarget(BufferTarget_t target);

	/*!
	 * \brief
	 *    Получает целевой тип буфера.
	 */
	virtual BufferTarget_t getTarget() const;

	/*!
	 * \brief
	 *    Устанавливает режим работы с данными.
	 * 
	 * \param[in] usage
	 *    Режим работы.
	 */
	virtual void setUsage(BufferUsage_t usage);
	
	/*!
	* \brief
	*    Получает режим работы с данными.
	*/
	virtual BufferUsage_t getUsage() const;

	/*!
	 * \brief
	 *    Устанавливает количество элементов в массиве.
	 * 
	 * \param[in] capacity
	 *    Количество элементов в массиве.
	 */
	virtual void setCapacity(s32_t capacity);

	/*!
	 * \brief
	 *    Получает количество элементов в массиве.
	 */
	virtual s32_t getCapacity() const;

	/*!
	 * \brief
	 *    Устанавливает размер структуры данных.
	 * 
	 * \param[in] stride
	 *    Размер структуры.
	 */
	virtual void setByteStride(s32_t stride);
	
	/*!
	 * \brief
	 *    Получает размер структуры данных.
	 */
	virtual s32_t getByteStride() const;

private:
	s32_t _allocedSize;
	u32_t _target;
	u32_t _usage;
	s32_t _capacity;
	s32_t _byteStride;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_BUFFER_H
