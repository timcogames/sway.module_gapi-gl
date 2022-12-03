#ifndef SWAY_GAPI_GL_EXCEPTIONS_HPP
#define SWAY_GAPI_GL_EXCEPTIONS_HPP

#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/prereqs.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class ShaderException : public core::runtime::Exception {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  ShaderException(u32_t objectId)
      : core::runtime::Exception([objectId]() -> std::string {
        std::string result;
        s32_t logLength;

#ifdef _EMSCRIPTEN
        glGetShaderiv(objectId, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
          auto logInfo = std::make_unique<GLchar[]>(logLength);
          glGetShaderInfoLog(objectId, logLength, NULL, logInfo.get());

          result = std::string(logInfo.get());
        }
#else
        Extension::glGetObjectParameteriv(objectId, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
        if (logLength > 0) {
          auto logInfo = std::make_unique<GLchar[]>(logLength);
          Extension::glGetInfoLog(objectId, logLength, NULL, logInfo.get());

          result = std::string(logInfo.get());
        }
#endif

        return result;
      }()) {
    // Empty
  }
};

class ShaderCompilationException : public ShaderException {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  ShaderCompilationException(u32_t objectId)
      : ShaderException(objectId) {
    // Empty
  }
};

class ShaderProgramLinkageException : public ShaderException {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  ShaderProgramLinkageException(u32_t objectId)
      : ShaderException(objectId) {
    // Empty
  }
};

class ShaderProgramValidationException : public ShaderException {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  ShaderProgramValidationException(u32_t objectId)
      : ShaderException(objectId) {
    // Empty
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif
