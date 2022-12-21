#ifndef SWAY_GAPI_GL_OGLEXCEPTIONS_HPP
#define SWAY_GAPI_GL_OGLEXCEPTIONS_HPP

#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/prereqs.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLShaderException : public core::runtime::Exception {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  OGLShaderException(u32_t objectId)
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

class OGLShaderCompilationException : public OGLShaderException {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  OGLShaderCompilationException(u32_t objectId)
      : OGLShaderException(objectId) {
    // Empty
  }
};

class OGLShaderProgramLinkageException : public OGLShaderException {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  OGLShaderProgramLinkageException(u32_t objectId)
      : OGLShaderException(objectId) {
    // Empty
  }
};

class OGLShaderProgramValidationException : public OGLShaderException {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  OGLShaderProgramValidationException(u32_t objectId)
      : OGLShaderException(objectId) {
    // Empty
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLEXCEPTIONS_HPP
