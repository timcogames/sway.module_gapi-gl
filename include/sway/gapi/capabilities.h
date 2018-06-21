#ifndef SWAY_GAPI_CAPABILITIES_H
#define SWAY_GAPI_CAPABILITIES_H

#include <sway/gapi/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class Capabilities {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Capabilities() = default;

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	~Capabilities() = default;

	/*!
	 * \brief
	 *    Получает GL версию.
	 */
	core::Version getGLVersion() const;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_CAPABILITIES_H
