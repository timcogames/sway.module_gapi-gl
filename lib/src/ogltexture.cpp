#include <sway/gapi/gl/ogltexture.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLTexture::createInstance() -> TextureRef_t {
  auto instance = std::make_shared<OGLTexture>(64, 64);
  return instance;
}

OGLTexture::OGLTexture(int width, int height) {
  std::vector<u8_t> image(width * height * 4);
  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      auto col = (((x & 0x8) == 0) ^ ((y & 0x8) == 0)) * 255;
      image[(y * width + x) * 4 + 0] = (GLubyte)col;
      image[(y * width + x) * 4 + 1] = (GLubyte)col;
      image[(y * width + x) * 4 + 2] = (GLubyte)col;
      image[(y * width + x) * 4 + 3] = 255;
    }
  }

  u32_t objname;
  glGenTextures(1, &objname);
  setUid(objname);

  glBindTexture(GL_TEXTURE_2D, getUid().value());
  helper_.TextureImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void OGLTexture::bind() {
  helper_.setActiveTexture(getUid().value());
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, getUid().value());
}

void OGLTexture::unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
