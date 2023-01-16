#include <sway/gapi/gl/ogltexture.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLTexture::createInstance() -> TextureRef_t {
  auto instance = std::make_shared<OGLTexture>();
  return instance;
}

OGLTexture::OGLTexture() {
  u32_t objname;
  helper_.generateTextures(1, &objname);
  setUid(objname);
}

void OGLTexture::create(void *data, int width, int height) {
  helper_.bindTexture(GL_TEXTURE_2D, getUid());
  helper_.TextureImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  helper_.bindTexture(GL_TEXTURE_2D, 0);
}

void OGLTexture::setActive(s32_t slot) { helper_.setActiveTexture(GL_TEXTURE0_ARB + slot); }

void OGLTexture::bind() {
  // glEnable(GL_TEXTURE_2D);
  helper_.bindTexture(GL_TEXTURE_2D, getUid());
}

void OGLTexture::unbind() {
  helper_.bindTexture(GL_TEXTURE_2D, 0);
  // glDisable(GL_TEXTURE_2D);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
