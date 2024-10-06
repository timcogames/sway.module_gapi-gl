#include <sway/gapi/gl/ogltexturesampler.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLTextureSampler::filterToGLenum(TextureFilter::Enum filter) -> GLenum {
  switch (filter) {
    case TextureFilter::Enum::NEAREST:
      return GL_NEAREST;
    case TextureFilter::Enum::NEAREST_MIPMAP_NEAREST:
      return GL_NEAREST_MIPMAP_NEAREST;
    case TextureFilter::Enum::NEAREST_MIPMAP_LINEAR:
      return GL_NEAREST_MIPMAP_LINEAR;
    case TextureFilter::Enum::LINEAR:
      return GL_LINEAR;
    case TextureFilter::Enum::LINEAR_MIPMAP_NEAREST:
      return GL_LINEAR_MIPMAP_NEAREST;
    case TextureFilter::Enum::LINEAR_MIPMAP_LINEAR:
      return GL_LINEAR_MIPMAP_LINEAR;
    default:
      return GL_NEAREST;
  }
}

auto OGLTextureSampler::wrapToGLenum(TextureWrap::Enum wrap) -> GLenum {
  switch (wrap) {
    case TextureWrap::Enum::REPEAT:
      return GL_REPEAT;
    case TextureWrap::Enum::CLAMP:
      return GL_CLAMP_TO_EDGE;
    default:
      return GL_REPEAT;
  }
}

auto OGLTextureSampler::createInstance(TexturePtr_t texture) -> TextureSamplerPtr_t {
  auto *instance = new OGLTextureSampler(texture);
  return instance;
}

OGLTextureSampler::OGLTextureSampler(TexturePtr_t texture)
    : helper_(new OGLTextureHelper())
    , texture_(texture) {}

OGLTextureSampler::~OGLTextureSampler() { SAFE_DELETE_OBJECT(helper_); }

void OGLTextureSampler::setWrapMode(TextureWrap::Enum wrapS, TextureWrap::Enum wrapT, TextureWrap::Enum wrapR) {
  texture_->bind();
  helper_->setTextureParamI(texture_->getTarget(), GL_TEXTURE_WRAP_S, OGLTextureSampler::wrapToGLenum(wrapS));
  helper_->setTextureParamI(texture_->getTarget(), GL_TEXTURE_WRAP_T, OGLTextureSampler::wrapToGLenum(wrapT));
  helper_->setTextureParamI(texture_->getTarget(), GL_TEXTURE_WRAP_R, OGLTextureSampler::wrapToGLenum(wrapR));
  texture_->unbind();
}

void OGLTextureSampler::setFilterMode(TextureFilter::Enum minFilter, TextureFilter::Enum magFilter) {
  texture_->bind();
  helper_->setTextureParamI(texture_->getTarget(), GL_TEXTURE_MAG_FILTER, OGLTextureSampler::filterToGLenum(minFilter));
  helper_->setTextureParamI(texture_->getTarget(), GL_TEXTURE_MIN_FILTER, OGLTextureSampler::filterToGLenum(magFilter));
  texture_->unbind();
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
