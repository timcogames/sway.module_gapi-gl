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
  void EMU_GenerateBuffers(u32_t latest, u32_t num, u32_t *ids);
  void STD_GenerateBuffers(u32_t latest, u32_t num, u32_t *ids);
  void ARB_GenerateBuffers(u32_t latest, u32_t num, u32_t *ids);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, deleteBuffers, u32_t, u32_t *)
  void EMU_DeleteBuffers(u32_t num, u32_t *ids);
  void STD_DeleteBuffers(u32_t num, u32_t *ids);
  void ARB_DeleteBuffers(u32_t num, u32_t *ids);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bindBuffer, u32_t, u32_t)
  void EMU_BindBuffer(u32_t target, u32_t buffer);
  void STD_BindBuffer(u32_t target, u32_t buffer);
  void ARB_BindBuffer(u32_t target, u32_t buffer);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bufferData, u32_t, ptrdiff_t, const void *, u32_t)
  void EMU_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage);
  void STD_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage);
  void ARB_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bufferSubData, u32_t, ptrdiff_t, ptrdiff_t, const void *)
  void EMU_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data);
  void STD_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data);
  void ARB_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data);

  DECLARE_GENERIC_MEMBER(void *, OGLGenericBufferHelper, mapBuffer, u32_t, u32_t)
  auto EMU_MapBuffer(u32_t target, u32_t access) -> void *;
  auto STD_MapBuffer(u32_t target, u32_t access) -> void *;
  auto ARB_MapBuffer(u32_t target, u32_t access) -> void *;

  DECLARE_GENERIC_MEMBER(void *, OGLGenericBufferHelper, mapBufferRange, u32_t, s32_t, s32_t, u32_t)
  auto EMU_MapBufferRange(u32_t target, s32_t offset, s32_t length, u32_t access) -> void *;
  auto STD_MapBufferRange(u32_t target, s32_t offset, s32_t length, u32_t access) -> void *;
  auto EXT_MapBufferRange(u32_t target, s32_t offset, s32_t length, u32_t access) -> void *;

  DECLARE_GENERIC_MEMBER(u8_t, OGLGenericBufferHelper, unmapBuffer, u32_t)
  auto EMU_UnmapBuffer(u32_t target) -> u8_t;
  auto STD_UnmapBuffer(u32_t target) -> u8_t;
  auto ARB_UnmapBuffer(u32_t target) -> u8_t;

  DECLARE_GENERIC_MEMBER(u8_t, OGLGenericBufferHelper, isBuffer, u32_t)
  auto EMU_IsBuffer(u32_t buffer) -> u8_t;
  auto STD_IsBuffer(u32_t buffer) -> u8_t;
  auto ARB_IsBuffer(u32_t buffer) -> u8_t;

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, getBufferParam, u32_t, u32_t, s32_t *)
  void EMU_GetBufferParam(u32_t target, u32_t pname, s32_t *params);
  void STD_GetBufferParam(u32_t target, u32_t pname, s32_t *params);
  void ARB_GetBufferParam(u32_t target, u32_t pname, s32_t *params);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP
