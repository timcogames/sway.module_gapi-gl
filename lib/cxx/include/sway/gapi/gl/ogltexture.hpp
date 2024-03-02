#ifndef SWAY_GAPI_GL_OGLTEXTURE_HPP
#define SWAY_GAPI_GL_OGLTEXTURE_HPP

#include <sway/gapi.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>
#include <sway/gapi/texturecreateinfo.hpp>
#include <sway/gapi/texturesubdatadescriptor.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLTexture : public Texture {
public:
  static auto createInstance(const TextureCreateInfo &createInfo) -> TexturePtr_t;

  OGLTexture(TextureTarget target);

  virtual ~OGLTexture() = default;

  MTHD_OVERRIDE(void create(const TextureCreateInfo &createInfo));

  MTHD_OVERRIDE(void updateSubdata(TextureSubdataDescriptor desc));

  MTHD_OVERRIDE(void setUnpackAlignement(u32_t param));

  MTHD_OVERRIDE(void setActive(s32_t slot));

  MTHD_OVERRIDE(void bind());

  MTHD_OVERRIDE(void unbind());

  // clang-format off
  MTHD_OVERRIDE(auto getTarget() -> TextureTarget) { return target_; }  // clang-format on

private:
  OGLTextureHelper *helper_;
  TextureTarget target_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLTEXTURE_HPP
