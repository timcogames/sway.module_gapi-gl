#ifndef SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/buffertargets.hpp>
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

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bindBuffer, BufferTarget, u32_t)
  void EMU_BindBuffer(BufferTarget target, u32_t buffer);
  void STD_BindBuffer(BufferTarget target, u32_t buffer);
  void ARB_BindBuffer(BufferTarget target, u32_t buffer);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bufferData, BufferTarget, ptrdiff_t, const void *, u32_t)
  void EMU_BufferData(BufferTarget target, ptrdiff_t size, const void *data, u32_t usage);
  void STD_BufferData(BufferTarget target, ptrdiff_t size, const void *data, u32_t usage);
  void ARB_BufferData(BufferTarget target, ptrdiff_t size, const void *data, u32_t usage);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bufferSubData, BufferTarget, ptrdiff_t, ptrdiff_t, const void *)
  void EMU_BufferSubData(BufferTarget target, ptrdiff_t offset, ptrdiff_t size, const void *data);
  void STD_BufferSubData(BufferTarget target, ptrdiff_t offset, ptrdiff_t size, const void *data);
  void ARB_BufferSubData(BufferTarget target, ptrdiff_t offset, ptrdiff_t size, const void *data);

  DECLARE_GENERIC_MEMBER(void *, OGLGenericBufferHelper, mapBuffer, BufferTarget, u32_t)
  auto EMU_MapBuffer(BufferTarget target, u32_t access) -> void *;
  auto STD_MapBuffer(BufferTarget target, u32_t access) -> void *;
  auto ARB_MapBuffer(BufferTarget target, u32_t access) -> void *;

  DECLARE_GENERIC_MEMBER(void *, OGLGenericBufferHelper, mapBufferRange, BufferTarget, s32_t, s32_t, u32_t)
  auto EMU_MapBufferRange(BufferTarget target, s32_t offset, s32_t length, u32_t access) -> void *;
  auto STD_MapBufferRange(BufferTarget target, s32_t offset, s32_t length, u32_t access) -> void *;
  auto EXT_MapBufferRange(BufferTarget target, s32_t offset, s32_t length, u32_t access) -> void *;

  DECLARE_GENERIC_MEMBER(u8_t, OGLGenericBufferHelper, unmapBuffer, BufferTarget)
  auto EMU_UnmapBuffer(BufferTarget target) -> u8_t;
  auto STD_UnmapBuffer(BufferTarget target) -> u8_t;
  auto ARB_UnmapBuffer(BufferTarget target) -> u8_t;

  DECLARE_GENERIC_MEMBER(u8_t, OGLGenericBufferHelper, isBuffer, u32_t)
  auto EMU_IsBuffer(u32_t buffer) -> u8_t;
  auto STD_IsBuffer(u32_t buffer) -> u8_t;
  auto ARB_IsBuffer(u32_t buffer) -> u8_t;

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, getBufferParam, BufferTarget, u32_t, s32_t *)
  void EMU_GetBufferParam(BufferTarget target, u32_t pname, s32_t *params);
  void STD_GetBufferParam(BufferTarget target, u32_t pname, s32_t *params);
  void ARB_GetBufferParam(BufferTarget target, u32_t pname, s32_t *params);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP
