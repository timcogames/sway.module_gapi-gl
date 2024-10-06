#ifndef SWAY_GAPI_GL_OGLTEXTURESAMPLER_HPP
#define SWAY_GAPI_GL_OGLTEXTURESAMPLER_HPP

#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLTextureSampler : public TextureSampler {
public:
  static auto filterToGLenum(TextureFilter::Enum filter) -> GLenum;

  static auto wrapToGLenum(TextureWrap::Enum wrap) -> GLenum;

  static auto createInstance(TexturePtr_t texture) -> TextureSamplerPtr_t;

  OGLTextureSampler(TexturePtr_t texture);

  virtual ~OGLTextureSampler();

  MTHD_OVERRIDE(void setWrapMode(TextureWrap::Enum wrapS, TextureWrap::Enum wrapT, TextureWrap::Enum wrapR));

  MTHD_OVERRIDE(void setFilterMode(TextureFilter::Enum minFilter, TextureFilter::Enum magFilter));

private:
  OGLTextureHelper *helper_;
  TexturePtr_t texture_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLTEXTURESAMPLER_HPP
