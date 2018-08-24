#ifndef SWAY_GAPI_GL_VIEWPORT_H
#define SWAY_GAPI_GL_VIEWPORT_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class Viewport : public IViewportBase {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Viewport();

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	virtual ~Viewport() = default;

	/*!
	 * \brief
	 *    Устанавливает новые значения прямоугольной области.
	 *
	 * \param[in] x
	 *    Значение координаты по оси X.
	 * 
	 * \param[in] y
	 *    Значение координаты по оси Y.
	 * 
	 * \param[in] w
	 *    Значение ширины.
	 * 
	 * \param[in] h
	 *    Значение высоты.
	 */
	virtual void set(s32_t x, s32_t y, s32_t w, s32_t h);

	/*!
	 * \brief
	 *    Устанавливает размер прямоугольной области.
	 *
	 * \param[in] w
	 *    Значение ширины.
	 * 
	 * \param[in] h
	 *    Значение высоты.
	 */
	virtual void set(s32_t w, s32_t h);

	/*!
	 * \brief
	 *    Получает размер прямоугольной области.
	 */
	virtual math::rect4i_t get() const;

	/*!
	 * \brief
	 *    Получает соотношение сторон.
	 */
	virtual f32_t aspect() const;

private:
	ViewportMode_t _mode;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_VIEWPORT_H
