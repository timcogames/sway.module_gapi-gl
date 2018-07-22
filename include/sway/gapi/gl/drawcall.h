#ifndef SWAY_GAPI_GL_DRAWCALL_H
#define SWAY_GAPI_GL_DRAWCALL_H

#include <sway/gapi/gl/bufferobject.h>
#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct DrawElements {
	u32_t mode;
	s32_t count;
	u32_t type;
};

struct DrawArrays {
	u32_t mode;
	s32_t first;
	s32_t count;
};

class DrawCall : public IDrawCallBase {
public:
#pragma region "Преобразование внутренних типов к GLenum"

	/*!
	 * \brief
	 *    Переводит тип топологии (режим отображение примитива) в GL.
	 */
	static GLenum topologyToGLenum(PrimitiveType_t topology);

#pragma endregion

	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	DrawCall() {
		// Empty
	}

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	virtual ~DrawCall() {
		// Empty
	}

	/*!
	 * \brief
	 *    Выполняет отрисовку примитива.
	 * 
	 * \param[in] topology
	 *    Топология примитива.
	 * 
	 * \param[in] count
	 *    Количество отображаемых элементов.
	 * 
	 * \param[in] ibo
	 *    Указатель на буфер индексов.
	 * 
	 * \param[in] type
	 *    Тип значений в индексах.
	 */
	virtual void execute(PrimitiveType_t topology, s32_t count, IBufferBase * ibo, Type_t type);

private:
	/*!
	 * \brief
	 *    Выводит примитивы по данным в массивах.
	 * 
	 * \sa
	 *    _drawIndexed(BufferObject *)
	 */
	void _draw(BufferObject * ibo);

	/*!
	 * \brief
	 *    Выводит индексные примитивы по данным в массивах.
	 * 
	 * \sa
	 *    _draw(BufferObject *)
	 */
	void _drawIndexed(BufferObject * ibo);

private:
	boost::function<void (BufferObject *)> _drawCallFunc;

	union {
		DrawElements _drawElements;
		DrawArrays _drawArrays;
	};
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_DRAWCALL_H
