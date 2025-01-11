#ifndef SWAY_GAPI_GL_OGLTEXTURE_HPP
#define SWAY_GAPI_GL_OGLTEXTURE_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>
#include <sway/gapi/idgenerator.hpp>
#include <sway/gapi/pixelstoragemodes.hpp>
#include <sway/gapi/texturecreateinfo.hpp>
#include <sway/gapi/texturesubdatadescriptor.hpp>
#include <sway/gapi/texturetargets.hpp>

namespace sway::gapi {

class OGLTexture : public Texture {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance(typedefs::IdGeneratorPtr_t idgen, const TextureCreateInfo &createInfo)
      -> typedefs::TexturePtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  OGLTexture(typedefs::IdGeneratorPtr_t idgen, TextureTarget::Enum target);

  virtual ~OGLTexture() = default;

#pragma endregion

#pragma region "Overridden Texture methods"

  MTHD_OVERRIDE(void create(const TextureCreateInfo &createInfo));

  MTHD_OVERRIDE(void updateSubdata(TextureSubdataDescriptor desc));

  MTHD_OVERRIDE(void setPixelStorage(PixelStorageMode::Enum mode, u32_t param));

  MTHD_OVERRIDE(void setActive(i32_t slot));

  MTHD_OVERRIDE(void bind());

  MTHD_OVERRIDE(void unbind());

  MTHD_OVERRIDE(auto getTarget() -> TextureTarget::Enum) { return target_; }

#pragma endregion

private:
  OGLTextureHelper *helper_;
  TextureTarget::Enum target_;
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_OGLTEXTURE_HPP
