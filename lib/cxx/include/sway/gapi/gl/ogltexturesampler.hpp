#ifndef SWAY_GAPI_GL_OGLTEXTURESAMPLER_HPP
#define SWAY_GAPI_GL_OGLTEXTURESAMPLER_HPP

#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLTextureSampler : public TextureSampler {
public:
  static auto filterToGLenum(TextureFilter filter) -> GLenum;

  static auto wrapToGLenum(TextureWrap wrap) -> GLenum;

  static auto createInstance(TexturePtr_t texture) -> TextureSamplerPtr_t;

  OGLTextureSampler(TexturePtr_t texture);

  virtual ~OGLTextureSampler();

  MTHD_OVERRIDE(void setWrapMode(TextureWrap wrapS, TextureWrap wrapT, TextureWrap wrapR));

  MTHD_OVERRIDE(void setFilterMode(TextureFilter minFilter, TextureFilter magFilter));

private:
  OGLTextureHelper *helper_;
  TexturePtr_t texture_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLTEXTURESAMPLER_HPP
