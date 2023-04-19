#ifndef SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLGenericBufferHelper {
public:
  OGLGenericBufferHelper();

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, generateBuffers, u32_t, u32_t, u32_t *)
  void EMU_generateBuffers(u32_t latest, u32_t num, u32_t *ids);
  void STD_generateBuffers(u32_t latest, u32_t num, u32_t *ids);
  void ARB_generateBuffers(u32_t latest, u32_t num, u32_t *ids);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, deleteBuffers, u32_t, u32_t *)
  void EMU_deleteBuffers(u32_t num, u32_t *ids);
  void STD_deleteBuffers(u32_t num, u32_t *ids);
  void ARB_deleteBuffers(u32_t num, u32_t *ids);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bindBuffer, u32_t, u32_t)
  void EMU_bindBuffer(u32_t target, u32_t buffer);
  void STD_bindBuffer(u32_t target, u32_t buffer);
  void ARB_bindBuffer(u32_t target, u32_t buffer);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bufferData, u32_t, ptrdiff_t, const void *, u32_t)
  void EMU_bufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage);
  void STD_bufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage);
  void ARB_bufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bufferSubData, u32_t, ptrdiff_t, ptrdiff_t, const void *)
  void EMU_bufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data);
  void STD_bufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data);
  void ARB_bufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data);

  DECLARE_GENERIC_MEMBER(void *, OGLGenericBufferHelper, mapBuffer, u32_t, u32_t)
  auto EMU_mapBuffer(u32_t target, u32_t access) -> void *;
  auto STD_mapBuffer(u32_t target, u32_t access) -> void *;
  auto ARB_mapBuffer(u32_t target, u32_t access) -> void *;

  DECLARE_GENERIC_MEMBER(void *, OGLGenericBufferHelper, mapBufferRange, u32_t, s32_t, s32_t, u32_t)
  auto EMU_mapBufferRange(u32_t target, s32_t offset, s32_t length, u32_t access) -> void *;
  auto STD_mapBufferRange(u32_t target, s32_t offset, s32_t length, u32_t access) -> void *;
  auto EXT_mapBufferRange(u32_t target, s32_t offset, s32_t length, u32_t access) -> void *;

  DECLARE_GENERIC_MEMBER(u8_t, OGLGenericBufferHelper, unmapBuffer, u32_t)
  auto EMU_unmapBuffer(u32_t target) -> u8_t;
  auto STD_unmapBuffer(u32_t target) -> u8_t;
  auto ARB_unmapBuffer(u32_t target) -> u8_t;

  DECLARE_GENERIC_MEMBER(u8_t, OGLGenericBufferHelper, isBuffer, u32_t)
  auto EMU_isBuffer(u32_t buffer) -> u8_t;
  auto STD_isBuffer(u32_t buffer) -> u8_t;
  auto ARB_isBuffer(u32_t buffer) -> u8_t;

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, getBufferParam, u32_t, u32_t, s32_t *)
  void EMU_getBufferParam(u32_t target, u32_t pname, s32_t *params);
  void STD_getBufferParam(u32_t target, u32_t pname, s32_t *params);
  void ARB_getBufferParam(u32_t target, u32_t pname, s32_t *params);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP
