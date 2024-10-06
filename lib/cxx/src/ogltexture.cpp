#include <sway/gapi/gl/oglpixelstoragemodeconvertor.hpp>
#include <sway/gapi/gl/ogltexture.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLTexture::createInstance(IdGeneratorPtr_t idgen, const TextureCreateInfo &createInfo) -> TexturePtr_t {
  auto *instance = new OGLTexture(idgen, createInfo.target);
  instance->create(createInfo);
  return instance;
}

OGLTexture::OGLTexture(IdGeneratorPtr_t idgen, TextureTarget::Enum target)
    : helper_(new OGLTextureHelper())
    , target_(target) {
  setUid(idgen->getNextUid());
}

// RGBA/UNSIGNED_BYTE or RGBA32F/FLOAT formats
void OGLTexture::create(const TextureCreateInfo &createInfo) {
  if (createInfo.size.getW() <= 0 || createInfo.size.getH() <= 0) {
    return;
  }

  bind();
  helper_->textureImage2D(target_, createInfo.mipLevels, createInfo.internalFormat, createInfo.size, 0,
      createInfo.format, createInfo.dataType, createInfo.pixels);
  unbind();
}

void OGLTexture::updateSubdata(TextureSubdataDescriptor desc) {
  bind();
  helper_->texSubImage2D(target_, desc.level, desc.offset.getX(), desc.offset.getY(), desc.size.getW(),
      desc.size.getH(), desc.format, desc.type, desc.pixels);
  unbind();
}

void OGLTexture::setPixelStorage(PixelStorageMode::Enum mode, u32_t param) {
  glPixelStorei(OGLPixelStorageModeConvertor::toGLenum(mode), param);
}

void OGLTexture::setActive(i32_t slot) { helper_->setActiveTexture(GL_TEXTURE0_ARB + slot); }

void OGLTexture::bind() {
  // glEnable(GL_TEXTURE_2D);
  helper_->bindTexture(target_, getUid());
}

void OGLTexture::unbind() {
  helper_->bindTexture(target_, 0);
  // glDisable(GL_TEXTURE_2D);
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
