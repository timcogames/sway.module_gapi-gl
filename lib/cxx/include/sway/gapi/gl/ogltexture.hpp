#ifndef SWAY_GAPI_GL_OGLTEXTURE_HPP
#define SWAY_GAPI_GL_OGLTEXTURE_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>
#include <sway/gapi/idgenerator.hpp>
#include <sway/gapi/pixelstoragemodes.hpp>
#include <sway/gapi/texturecreateinfo.hpp>
#include <sway/gapi/texturesubdatadescriptor.hpp>
#include <sway/gapi/texturetargets.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLTexture : public Texture {
public:
  static auto createInstance(IdGeneratorPtr_t idgen, const TextureCreateInfo &createInfo) -> TexturePtr_t;

#pragma region "Ctors/Dtor"

  OGLTexture(IdGeneratorPtr_t idgen, TextureTarget target);

  virtual ~OGLTexture() = default;

#pragma endregion

  MTHD_OVERRIDE(void create(const TextureCreateInfo &createInfo));

  MTHD_OVERRIDE(void updateSubdata(TextureSubdataDescriptor desc));

  MTHD_OVERRIDE(void setPixelStorage(PixelStorageMode mode, u32_t param));

  MTHD_OVERRIDE(void setActive(i32_t slot));

  MTHD_OVERRIDE(void bind());

  MTHD_OVERRIDE(void unbind());

  MTHD_OVERRIDE(auto getTarget() -> TextureTarget) { return target_; }

private:
  OGLTextureHelper *helper_;
  TextureTarget target_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLTEXTURE_HPP
