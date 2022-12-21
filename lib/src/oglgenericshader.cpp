#include <sway/gapi/gl/oglexceptions.hpp>
#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/oglgenericshader.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLGenericShader::typeToGLenum(ShaderType type) -> GLenum {
#ifdef _EMSCRIPTEN
  switch (type) {
    case ShaderType::VERT:
      return GL_VERTEX_SHADER;
    case ShaderType::FRAG:
      return GL_FRAGMENT_SHADER;
    default:
      return GL_INVALID_INDEX;
  }
#else
  switch (type) {
    case ShaderType::VERT:
      return GL_VERTEX_SHADER_ARB;
    case ShaderType::FRAG:
      return GL_FRAGMENT_SHADER_ARB;
    default:
      return GL_INVALID_INDEX;
  }
#endif
}

auto OGLGenericShader::createInstance(const ShaderCreateInfo &createInfo) -> ShaderRef_t {
  // try {
  auto instance = std::make_shared<OGLGenericShader>(createInfo.type);
  // EM_ASM({ console.log('source: ' + UTF8ToString($0)); }, createInfo.code.c_str());
  instance->compile(createInfo.code.c_str());
  return instance;
  //} catch (std::exception &exception) {
  //  fprintf(stderr, "ERROR: %s shader object creation failed.\n", stringize(createInfo.type).c_str());
  //  throw;
  //}
}

OGLGenericShader::OGLGenericShader(ShaderType type)
    : Shader(type)
    , helper_(gapi::Extension::extensions)
    , type_(type)
    , compiled_(false) {
  auto objectId = helper_.CreateShader(OGLGenericShader::typeToGLenum(type_));
  if (objectId != 0) {
    setUid(objectId);
  }
}

OGLGenericShader::~OGLGenericShader() { helper_.DeleteShader(getUid()); }

void OGLGenericShader::compile(lpcstr_t source) {
  int compileStatus;
  // EM_ASM({ console.log('objectId_: ' + $0); }, objectId_);
  // EM_ASM({ console.log('source: ' + UTF8ToString($0)); }, source);

  helper_.ShaderSource(getUid(), 1, &source, nullptr);
  helper_.CompileShader(getUid());
  helper_.GetShaderParam(getUid(), GL_COMPILE_STATUS, &compileStatus);  // GL_OBJECT_COMPILE_STATUS_ARB
  compiled_ = (compileStatus == GL_TRUE);
  if (!compiled_) {
    throw OGLShaderCompilationException(getUid().value());
  }
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
