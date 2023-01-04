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

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, GenerateBuffers, u32_t, u32_t, u32_t *)
  void EMU_GenerateBuffers(u32_t latest, u32_t num, u32_t *ids);
  void STD_GenerateBuffers(u32_t latest, u32_t num, u32_t *ids);
  void ARB_GenerateBuffers(u32_t latest, u32_t num, u32_t *ids);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, DeleteBuffers, u32_t, u32_t *)
  void EMU_DeleteBuffers(u32_t num, u32_t *ids);
  void STD_DeleteBuffers(u32_t num, u32_t *ids);
  void ARB_DeleteBuffers(u32_t num, u32_t *ids);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, BindBuffer, u32_t, u32_t)
  void EMU_BindBuffer(u32_t target, u32_t buffer);
  void STD_BindBuffer(u32_t target, u32_t buffer);
  void ARB_BindBuffer(u32_t target, u32_t buffer);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, BufferData, u32_t, ptrdiff_t, const void *, u32_t)
  void EMU_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage);
  void STD_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage);
  void ARB_BufferData(u32_t target, ptrdiff_t size, const void *data, u32_t usage);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, BufferSubData, u32_t, ptrdiff_t, ptrdiff_t, const void *)
  void EMU_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data);
  void STD_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data);
  void ARB_BufferSubData(u32_t target, ptrdiff_t offset, ptrdiff_t size, const void *data);

  DECLARE_GENERIC_MEMBER(u8_t, OGLGenericBufferHelper, isBuffer, u32_t)
  auto EMU_isBuffer(u32_t buffer) -> u8_t;
  auto STD_isBuffer(u32_t buffer) -> u8_t;
  auto ARB_isBuffer(u32_t buffer) -> u8_t;

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, GetBufferParam, u32_t, u32_t, s32_t *)
  void EMU_GetBufferParam(u32_t target, u32_t pname, s32_t *params);
  void STD_GetBufferParam(u32_t target, u32_t pname, s32_t *params);
  void ARB_GetBufferParam(u32_t target, u32_t pname, s32_t *params);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP
