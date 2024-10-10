#ifndef SWAY_GAPI_GL_OGLFRAMEBUFFERIDGENERATOR_HPP
#define SWAY_GAPI_GL_OGLFRAMEBUFFERIDGENERATOR_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglframebufferhelper.hpp>
#include <sway/gapi/idgenerator.hpp>
#include <sway/gapi/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

#define BUFFER_IDS_CHUNK_CAPACITY 10

class OGLFrameBufferIdGenerator : public ObjectUidQueue_t, public IdGenerator {
public:
#pragma region "Static methods"

  static auto createInstance() -> IdGeneratorPtr_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  OGLFrameBufferIdGenerator();

  OGLFrameBufferIdGenerator(OGLFrameBufferHelperIface &helper);

  virtual ~OGLFrameBufferIdGenerator();

#pragma endregion

  [[nodiscard]]
  auto getNextUid() -> ObjectUid_t;

private:
  OGLFrameBufferHelperIface *helper_;
  ObjectUidVec_t used_;
  i32_t chunkCapacity_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLFRAMEBUFFERIDGENERATOR_HPP
