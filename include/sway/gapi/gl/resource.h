#ifndef SWAY_GAPI_GL_RESOURCE_H
#define SWAY_GAPI_GL_RESOURCE_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class Resource {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 */
	Resource()
		: _resourceId(0) {
		// Empty
	}

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	virtual ~Resource() = default;

	/*!
	 * \brief
	 *    Получает идентификатор ресурса.
	 */
	ResourceId_t getId() const {
		return _resourceId;
	}

protected:
	ResourceId_t _resourceId; /*!< Идентификатор ресурса. */
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_RESOURCE_H
