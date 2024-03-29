#include <sway/gapi/gl/oglgenericshader.hpp>
#include <sway/gapi/gl/oglshaderexceptions.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLGenericShader::typeToGLenum(ShaderType type) -> GLenum {
#ifdef EMSCRIPTEN_PLATFORM
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
    , helper_(new OGLGenericShaderHelper())
    , type_(type)
    , compiled_(false) {
  auto objectId = helper_->createShader(OGLGenericShader::typeToGLenum(type_));
  if (objectId != 0) {
    setUid(objectId);
  }
}

OGLGenericShader::OGLGenericShader(OGLGenericShaderHelperIface &helper, ShaderType type)
    : Shader(type)
    , helper_(&helper)
    , type_(type)
    , compiled_(false) {
  auto objectId = helper_->createShader(OGLGenericShader::typeToGLenum(type_));
  if (objectId != 0) {
    setUid(objectId);
  }
}

OGLGenericShader::~OGLGenericShader() {
  helper_->deleteShader(getUid());
  SAFE_DELETE_OBJECT(helper_);
}

auto OGLGenericShader::getAttribLocation(std::optional<u32_t> progId, lpcstr_t name) -> s32_t {
  return helper_->getAttribLocation(progId.value(), name);
}

void OGLGenericShader::compile(lpcstr_t src) {
  int status;  // Состояние шагов компилирования.
  helper_->shaderSource(getUid(), 1, &src, nullptr);
  helper_->compileShader(getUid(), &status);
  compiled_ = (status == GL_TRUE);
  if (!compiled_) {
    throw OGLShaderCompilationException(getUid().value());
  }
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
