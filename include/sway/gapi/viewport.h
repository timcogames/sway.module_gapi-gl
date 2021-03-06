#ifndef SWAY_GAPI_VIEWPORT_H
#define SWAY_GAPI_VIEWPORT_H

#include <sway/math.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class Viewport {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Viewport();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~Viewport();

	/*!
	 * \brief
	 *   Устанавливает новые значения прямоугольной области.
	 *
	 * \param[in] x
	 *   Значение координаты по оси X.
	 * 
	 * \param[in] y
	 *   Значение координаты по оси Y.
	 * 
	 * \param[in] w
	 *   Значение ширины.
	 * 
	 * \param[in] h
	 *   Значение высоты.
	 */
	void set(s32_t x, s32_t y, s32_t w, s32_t h);

	/*!
	 * \brief
	 *   Устанавливает размер прямоугольной области.
	 *
	 * \param[in] w
	 *   Значение ширины.
	 * 
	 * \param[in] h
	 *   Значение высоты.
	 */
	void set(s32_t w, s32_t h);

	/*!
	 * \brief
	 *   Получает размер прямоугольной области.
	 */
	math::TRect<s32_t> get() const;

	/*!
	 * \brief
	 *   Получает соотношение сторон.
	 */
	f32_t aspect() const;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_VIEWPORT_H
