#include <sway/gapi/gl/oglgenericshader.hpp>
#include <sway/gapi/gl/oglgenericshadertypeconvertor.hpp>
#include <sway/gapi/gl/oglshaderexceptions.hpp>
#include <sway/gapi/gl/oglshaderpreprocessor.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <sstream>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLGenericShader::createInstance(const ShaderCreateInfo &createInfo) -> ShaderPtr_t {
  // try {
  auto *preprocessor = static_cast<OGLShaderPreprocessor *>(createInfo.preprocessor);
  ShaderSource src;

  src.addVersion(preprocessor->getVersion());
  if (createInfo.type == ShaderType::Enum::FRAG) {
    src.addDefaultPrecision();
  }

  std::ostringstream preprocessedSource;
  preprocessedSource << src.toStr();

  preprocessor->evaluate(preprocessedSource);

  auto dataSource = preprocessedSource.str() + createInfo.code;

  // std::cout << dataSource.c_str() << std::endl;

  auto *instance = new OGLGenericShader(createInfo.type);
  // EM_ASM({ console.log('source: ' + UTF8ToString($0)); }, createInfo.code.c_str());
  instance->compile(dataSource.c_str());
  return instance;
  //} catch (std::exception &exception) {
  //  fprintf(stderr, "ERROR: %s shader object creation failed.\n", stringize(createInfo.type).c_str());
  //  throw;
  //}
}

OGLGenericShader::OGLGenericShader(ShaderType::Enum type)
    : Shader(type)
    , helper_(new OGLGenericShaderHelper())
    , type_(type)
    , compiled_(false) {
  auto objectId = helper_->createShader(OGLGenericShaderTypeConvertor::toGLenum(type_));
  if (objectId != 0) {
    setUid(objectId);
  }
}

OGLGenericShader::OGLGenericShader(OGLGenericShaderHelperIface &helper, ShaderType::Enum type)
    : Shader(type)
    , helper_(&helper)
    , type_(type)
    , compiled_(false) {
  auto objectId = helper_->createShader(OGLGenericShaderTypeConvertor::toGLenum(type_));
  if (objectId != 0) {
    setUid(objectId);
  }
}

OGLGenericShader::~OGLGenericShader() { helper_->deleteShader(getUid()); }

auto OGLGenericShader::getAttribLocation(std::optional<u32_t> progId, lpcstr_t name) -> i32_t {
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

NS_END()  // namespace gapi
NS_END()  // namespace sway
