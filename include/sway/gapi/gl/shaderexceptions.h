#ifndef SWAY_GAPI_GL_SHADEREXCEPTIONS_H
#define SWAY_GAPI_GL_SHADEREXCEPTIONS_H

#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class ShaderCompilationException : public Exception {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderCompilationException(const std::string & message)
		: Exception(message) {
		// Empty
	}
};

class ShaderLinkageException : public Exception {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderLinkageException(const std::string & message)
		: Exception(message) {
		// Empty
	}
};

class ShaderValidationException : public Exception {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderValidationException(const std::string & message)
		: Exception(message) {
		// Empty
	}
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_SHADEREXCEPTIONS_H
