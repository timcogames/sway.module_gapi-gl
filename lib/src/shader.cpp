#include <sway/gapi/gl/exceptions.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/shader.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto Shader::typeToGLenum(ShaderType_t type) -> GLenum {
#ifdef _EMSCRIPTEN
  switch (type) {
    case ShaderType_t::kVertex:
      return GL_VERTEX_SHADER;
    case ShaderType_t::kFragment:
      return GL_FRAGMENT_SHADER;
    default:
      return GL_INVALID_INDEX;
  }
#else
  switch (type) {
    case ShaderType_t::kVertex:
      return GL_VERTEX_SHADER_ARB;
    case ShaderType_t::kFragment:
      return GL_FRAGMENT_SHADER_ARB;
    default:
      return GL_INVALID_INDEX;
  }
#endif
}

auto Shader::createInstance(const ShaderCreateInfo &createInfo) -> ShaderRef_t {
  // try {
  auto instance = std::make_shared<Shader>(createInfo.type);
  // EM_ASM({ console.log('source: ' + UTF8ToString($0)); }, createInfo.code.c_str());
  instance->compile(createInfo.code.c_str());
  return instance;
  //} catch (std::exception &exception) {
  //  fprintf(stderr, "ERROR: %s shader object creation failed.\n", stringize(createInfo.type).c_str());
  //  throw;
  //}
}

Shader::Shader(ShaderType_t type)
    : AShaderBase(type)
    , _type(type)
    , _compiled(false) {
#ifdef _EMSCRIPTEN
  objectId_ = glCreateShader(Shader::typeToGLenum(_type));
#else
  objectId_ = Extension::glCreateShaderObject(Shader::typeToGLenum(_type));
#endif
}

Shader::~Shader() {
#ifdef _EMSCRIPTEN
  glDeleteShader(objectId_);
#else
  Extension::glDeleteShaderObject(objectId_);
#endif
}

void Shader::compile(lpcstr_t source) {
  int compileStatus;
#ifdef _EMSCRIPTEN
  // EM_ASM({ console.log('objectId_: ' + $0); }, objectId_);
  // EM_ASM({ console.log('source: ' + UTF8ToString($0)); }, source);
  glShaderSource(objectId_, 1, &source, NULL);
  glCompileShader(objectId_);
  glGetShaderiv(objectId_, GL_COMPILE_STATUS, &compileStatus);
#else
  Extension::glShaderSource(objectId_, 1, &source, NULL);
  Extension::glCompileShader(objectId_);
  Extension::glGetObjectParameteriv(objectId_, GL_OBJECT_COMPILE_STATUS_ARB, &compileStatus);
#endif
  _compiled = (compileStatus == GL_TRUE);
  if (!_compiled) {
    throw ShaderCompilationException(objectId_);
  }
}

auto Shader::isCompiled() const -> bool { return _compiled; }

auto Shader::getType() const -> ShaderType_t { return _type; }

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
