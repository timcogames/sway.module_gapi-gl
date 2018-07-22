#ifndef SWAY_GAPI_GL_SHADERUTILS_H
#define SWAY_GAPI_GL_SHADERUTILS_H

#include <sway/gapi/gl/extensions.h>
#include <sway/gapi/gl/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class ShaderUtils {
public:
	static std::string getErrorInfo(u32_t _objectId) {
		std::string result;
		GLint logLength;
		
		Extensions::glGetObjectParameterivARB(_objectId, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
		if (logLength > 0) {
			auto logInfo = boost::make_unique<GLchar[]>(logLength);
			Extensions::glGetInfoLogARB(_objectId, logLength, NULL, logInfo.get());

			result = std::string(logInfo.get());
		}

		return result;
	}
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_SHADERUTILS_H
