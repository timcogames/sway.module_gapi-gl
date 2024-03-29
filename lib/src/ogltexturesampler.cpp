#include <sway/gapi/gl/ogltexturesampler.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLTextureSampler::filterToGLenum(TextureFilter filter) -> GLenum {
  switch (filter) {
    case TextureFilter::NEAREST:
      return GL_NEAREST;
    case TextureFilter::NEAREST_MIPMAP_NEAREST:
      return GL_NEAREST_MIPMAP_NEAREST;
    case TextureFilter::NEAREST_MIPMAP_LINEAR:
      return GL_NEAREST_MIPMAP_LINEAR;
    case TextureFilter::LINEAR:
      return GL_LINEAR;
    case TextureFilter::LINEAR_MIPMAP_NEAREST:
      return GL_LINEAR_MIPMAP_NEAREST;
    case TextureFilter::LINEAR_MIPMAP_LINEAR:
      return GL_LINEAR_MIPMAP_LINEAR;
    default:
      return GL_NEAREST;
  }
}

auto OGLTextureSampler::wrapToGLenum(TextureWrap wrap) -> GLenum {
  switch (wrap) {
    case TextureWrap::REPEAT:
      return GL_REPEAT;
    case TextureWrap::CLAMP:
      return GL_CLAMP_TO_EDGE;
    default:
      return GL_REPEAT;
  }
}

auto OGLTextureSampler::createInstance() -> TextureSamplerRef_t {
  auto instance = std::make_shared<OGLTextureSampler>();
  return instance;
}

OGLTextureSampler::OGLTextureSampler()
    : helper_(new OGLTextureHelper()) {}

OGLTextureSampler::~OGLTextureSampler() { SAFE_DELETE_OBJECT(helper_); }

void OGLTextureSampler::setWrapMode(TextureWrap wrapS, TextureWrap wrapT, TextureWrap wrapR) {
  helper_->setTextureParamI(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, OGLTextureSampler::wrapToGLenum(wrapS));
  helper_->setTextureParamI(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, OGLTextureSampler::wrapToGLenum(wrapT));
  helper_->setTextureParamI(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, OGLTextureSampler::wrapToGLenum(wrapR));
}

void OGLTextureSampler::setFilterMode(TextureFilter minFilter, TextureFilter magFilter) {
  helper_->setTextureParamI(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, OGLTextureSampler::filterToGLenum(minFilter));
  helper_->setTextureParamI(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, OGLTextureSampler::filterToGLenum(magFilter));
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
