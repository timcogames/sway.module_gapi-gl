#include <sway/gapi/gl/ogltexture.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLTexture::createInstance(const TextureCreateInfo &createInfo) -> TextureRef_t {
  auto instance = std::make_shared<OGLTexture>(createInfo.target);
  instance->create(createInfo);
  return instance;
}

OGLTexture::OGLTexture(TextureTarget target)
    : helper_(new OGLTextureHelper())
    , target_(target) {
  u32_t objname;
  helper_->generateTextures(1, &objname);
  setUid(objname);
}

// RGBA/UNSIGNED_BYTE or RGBA32F/FLOAT formats
void OGLTexture::create(const TextureCreateInfo &createInfo) {
  if (createInfo.size.getW() <= 0 || createInfo.size.getH() <= 0) {
    return;
  }

  this->bind();
  helper_->textureImage2D(target_, createInfo.mipLevels, createInfo.internalFormat, createInfo.size, 0,
      createInfo.format, createInfo.dataType, createInfo.pixels);
  this->unbind();
}

void OGLTexture::updateSubdata(TextureSubdataDescriptor desc) {
  this->bind();
  helper_->texSubImage2D(target_, desc.level, desc.offset.getX(), desc.offset.getY(), desc.size.getW(),
      desc.size.getH(), desc.format, desc.type, desc.pixels);
  this->unbind();
}

void OGLTexture::setUnpackAlignement(u32_t param) { glPixelStorei(GL_UNPACK_ALIGNMENT, param); }

void OGLTexture::setActive(s32_t slot) { helper_->setActiveTexture(GL_TEXTURE0_ARB + slot); }

void OGLTexture::bind() {
  // glEnable(GL_TEXTURE_2D);
  helper_->bindTexture(target_, getUid());
}

void OGLTexture::unbind() {
  helper_->bindTexture(target_, 0);
  // glDisable(GL_TEXTURE_2D);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
