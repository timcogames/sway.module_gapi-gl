#include <sway/gapi/gl/ogltexture.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLTexture::createInstance() -> TextureRef_t {
  auto instance = std::make_shared<OGLTexture>(64, 64);
  return instance;
}

OGLTexture::OGLTexture(int width, int height) {
  u8_t pixels[height][width][4];
  int c;
  for (auto i = 0; i < height; i++) {
    for (auto j = 0; j < width; j++) {
      c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
      pixels[i][j][0] = (GLubyte)c;
      pixels[i][j][1] = (GLubyte)c;
      pixels[i][j][2] = (GLubyte)c;
      pixels[i][j][3] = (GLubyte)255;
    }
  }

  u32_t objname;
  glGenTextures(1, &objname);
  setUid(objname);

  glBindTexture(GL_TEXTURE_2D, getUid().value());
  helper_.TextureImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void OGLTexture::bind() {
  glActiveTexture(getUid().value());
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, getUid().value());
}

void OGLTexture::unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
