#ifndef SWAY_GAPI_GL_OGLTEXTUREIDGENERATOR_HPP
#define SWAY_GAPI_GL_OGLTEXTUREIDGENERATOR_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>
#include <sway/gapi/idgenerator.hpp>
#include <sway/gapi/typedefs.hpp>

#include <queue>

namespace sway::gapi {

#define TEXTURE_IDS_CHUNK_CAPACITY 10

class OGLTextureIdGenerator : public ObjectUidQueue_t, public IdGenerator {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance() -> typedefs::IdGeneratorPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  OGLTextureIdGenerator();

  DTOR_VIRTUAL(OGLTextureIdGenerator);

#pragma endregion

  [[nodiscard]] auto getNextUid() -> ObjectUid_t;

private:
  OGLTextureHelper helper_;
  ObjectUidVec_t used_;
  i32_t chunkCapacity_;
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_OGLTEXTUREIDGENERATOR_HPP
