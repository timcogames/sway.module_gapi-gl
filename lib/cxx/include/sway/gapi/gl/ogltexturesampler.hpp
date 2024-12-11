#ifndef SWAY_GAPI_GL_OGLTEXTURESAMPLER_HPP
#define SWAY_GAPI_GL_OGLTEXTURESAMPLER_HPP

#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLTextureSampler : public TextureSampler {
public:
#pragma region "Static methods"

  static auto filterToGLenum(TextureFilter::Enum filter) -> GLenum;

  static auto wrapToGLenum(TextureWrap::Enum wrap) -> GLenum;

  /**
   * @name creators
   * @{
   */

  static auto createInstance(TexturePtr_t texture) -> TextureSamplerPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  OGLTextureSampler(TexturePtr_t texture);

  DTOR_VIRTUAL(OGLTextureSampler);

#pragma endregion

#pragma region "Overridden TextureSampler methods"

  MTHD_OVERRIDE(void setWrapMode(TextureWrap::Enum wrapS, TextureWrap::Enum wrapT, TextureWrap::Enum wrapR));

  MTHD_OVERRIDE(void setFilterMode(TextureFilter::Enum minFilter, TextureFilter::Enum magFilter));

#pragma endregion

private:
  OGLTextureHelper *helper_;
  TexturePtr_t texture_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLTEXTURESAMPLER_HPP
