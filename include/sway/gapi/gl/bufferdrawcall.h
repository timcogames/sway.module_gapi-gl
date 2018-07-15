#ifndef SWAY_GAPI_GL_BUFFERDRAWCALL_H
#define SWAY_GAPI_GL_BUFFERDRAWCALL_H

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

class BufferDrawCall {
public:
#pragma region "Преобразование внутренних типов к GLenum"

	/*!
	 * \brief
	 *    Переводит тип топологии (режим отображение примитива) в GL.
	 */
	static GLenum topologyToGLenum(u32_t topology);

#pragma endregion

	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	BufferDrawCall() = default;

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	~BufferDrawCall() = default;

	void update(u32_t topology, s32_t count, Type_t type, bool indexed);

	void execute(BufferObject * ibo);

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

#endif // SWAY_GAPI_GL_BUFFERDRAWCALL_H
