#ifndef SWAY_GAPI_GL_OGLIDGENERATOR_HPP
#define SWAY_GAPI_GL_OGLIDGENERATOR_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglidgeneratorhelper.hpp>
#include <sway/gapi/idgenerator.hpp>
#include <sway/gapi/idgeneratortypes.hpp>
#include <sway/gapi/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

#define BUFFER_IDS_CHUNK_CAPACITY 10

template <IdGeneratorType::Enum TYPE>
class OGLIdGenerator : public ObjectUidQueue_t, public IdGenerator {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance() -> IdGeneratorPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  OGLIdGenerator();

  OGLIdGenerator(OGLIdGeneratorHelper<TYPE> &helper);

  DTOR_VIRTUAL(OGLIdGenerator);

#pragma endregion

  [[nodiscard]] auto getNextUid() -> ObjectUid_t;

private:
  OGLIdGeneratorHelper<TYPE> *helper_;
  ObjectUidVec_t used_;
  i32_t chunkCapacity_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#include <sway/gapi/gl/oglidgenerator.inl>

#endif  // SWAY_GAPI_GL_OGLIDGENERATOR_HPP
