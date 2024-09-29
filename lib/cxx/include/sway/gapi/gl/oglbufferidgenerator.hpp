#ifndef SWAY_GAPI_GL_OGLBUFFERIDGENERATOR_HPP
#define SWAY_GAPI_GL_OGLBUFFERIDGENERATOR_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglgenericbufferhelper.hpp>
#include <sway/gapi/idgenerator.hpp>
#include <sway/gapi/typedefs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

#define BUFFER_IDS_CHUNK_CAPACITY 10

class OGLBufferIdGenerator : public ObjectUidQueue_t, public IdGenerator {
public:
#pragma region "Static methods"

  static auto createInstance() -> IdGeneratorPtr_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  OGLBufferIdGenerator();

  OGLBufferIdGenerator(OGLGenericBufferHelperIface &helper);

  virtual ~OGLBufferIdGenerator();

#pragma endregion

  [[nodiscard]]
  auto getNextUid() -> ObjectUid_t;

private:
  OGLGenericBufferHelperIface *helper_;
  ObjectUidVec_t used_;
  i32_t chunkCapacity_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLBUFFERIDGENERATOR_HPP
