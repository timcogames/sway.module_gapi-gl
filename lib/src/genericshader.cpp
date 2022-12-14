#include <sway/gapi/gl/exceptions.hpp>
#include <sway/gapi/gl/extensions.hpp>
#include <sway/gapi/gl/genericshader.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto GenericShader::typeToGLenum(ShaderType_t type) -> GLenum {
#ifdef _EMSCRIPTEN
  switch (type) {
    case ShaderType_t::Vertex:
      return GL_VERTEX_SHADER;
    case ShaderType_t::Fragment:
      return GL_FRAGMENT_SHADER;
    default:
      return GL_INVALID_INDEX;
  }
#else
  switch (type) {
    case ShaderType_t::Vertex:
      return GL_VERTEX_SHADER_ARB;
    case ShaderType_t::Fragment:
      return GL_FRAGMENT_SHADER_ARB;
    default:
      return GL_INVALID_INDEX;
  }
#endif
}

auto GenericShader::createInstance(const ShaderCreateInfo &createInfo) -> ShaderRef_t {
  // try {
  auto instance = std::make_shared<GenericShader>(createInfo.type);
  // EM_ASM({ console.log('source: ' + UTF8ToString($0)); }, createInfo.code.c_str());
  instance->compile(createInfo.code.c_str());
  return instance;
  //} catch (std::exception &exception) {
  //  fprintf(stderr, "ERROR: %s shader object creation failed.\n", stringize(createInfo.type).c_str());
  //  throw;
  //}
}

GenericShader::GenericShader(ShaderType_t type)
    : Shader(type)
    , shaderHelper_(gapi::Extension::extensions)
    , type_(type)
    , compiled_(false) {
  auto objectId = shaderHelper_.CreateShader(GenericShader::typeToGLenum(type_));
  if (objectId != 0) {
    setUid(objectId);
  }
}

GenericShader::~GenericShader() { shaderHelper_.DeleteShader(getUid()); }

void GenericShader::compile(lpcstr_t source) {
  int compileStatus;
  // EM_ASM({ console.log('objectId_: ' + $0); }, objectId_);
  // EM_ASM({ console.log('source: ' + UTF8ToString($0)); }, source);

  shaderHelper_.ShaderSource(getUid(), 1, &source, nullptr);
  shaderHelper_.CompileShader(getUid());
  shaderHelper_.GetShaderParam(getUid(), GL_COMPILE_STATUS, &compileStatus);  // GL_OBJECT_COMPILE_STATUS_ARB
  compiled_ = (compileStatus == GL_TRUE);
  if (!compiled_) {
    throw ShaderCompilationException(getUid().value());
  }
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
