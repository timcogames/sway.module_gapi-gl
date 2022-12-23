#include <sway/gapi/gl/ogltexture.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLTexture::createInstance() -> TextureRef_t {
  auto instance = std::make_shared<OGLTexture>();
  return instance;
}

OGLTexture::OGLTexture() {}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
