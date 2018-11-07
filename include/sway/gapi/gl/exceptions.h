#ifndef SWAY_GAPI_GL_EXCEPTIONS_H
#define SWAY_GAPI_GL_EXCEPTIONS_H

#include <sway/gapi/gl/extensions.h>
#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class ShaderException : public Exception {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderException(u32_t objectId)
		: Exception([objectId]() -> std::string {
			std::string result;
			s32_t logLength;
			
			Extension::glGetObjectParameteriv(objectId, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
			if (logLength > 0) {
				auto logInfo = boost::make_unique<GLchar[]>(logLength);
				Extension::glGetInfoLog(objectId, logLength, NULL, logInfo.get());
				
				result = std::string(logInfo.get());
			}

			return result;
		}()) {
		// Empty
	}
};

class ShaderCompilationException : public ShaderException {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderCompilationException(u32_t objectId)
		: ShaderException(objectId) {
		// Empty
	}
};

class ShaderProgramLinkageException : public ShaderException {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderProgramLinkageException(u32_t objectId)
		: ShaderException(objectId) {
		// Empty
	}
};

class ShaderProgramValidationException : public ShaderException {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	ShaderProgramValidationException(u32_t objectId)
		: ShaderException(objectId) {
		// Empty
	}
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_EXCEPTIONS_H
