#ifndef SWAY_GAPI_CAPABILITIES_H
#define SWAY_GAPI_CAPABILITIES_H

#include <sway/core.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class Capabilities {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Capabilities();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~Capabilities();

	/*!
	 * \brief
	 *    Получает GL версию.
	 */
	core::Version getVersion();
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_CAPABILITIES_H
