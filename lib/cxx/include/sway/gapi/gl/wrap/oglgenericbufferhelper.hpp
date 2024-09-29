#ifndef SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/buffertargets.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>
#include <sway/gapi/typedefs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLGenericBufferHelperIface {
public:
  virtual ~OGLGenericBufferHelperIface() = default;

  PURE_VIRTUAL(void generateBuffers(u32_t latest, u32_t num, u32_t *uids));

  PURE_VIRTUAL(void deleteBuffers(u32_t num, u32_t *uids));
};

class OGLGenericBufferHelper : public OGLGenericBufferHelperIface {
public:
  OGLGenericBufferHelper();

  virtual ~OGLGenericBufferHelper() = default;

  // clang-format off
  DECL_GENERIC_CALLBACK_FUNC(void, OGLGenericBufferHelper, generateBuffers, u32_t, u32_t, ObjectUid_t *)
  MTHD_VIRTUAL(void generateBuffers(u32_t latest, u32_t num, ObjectUid_t *uids) { 
     (this->*generateBuffers_)(latest, num, uids); 
  });
  // clang-format on

  void EMU_GenerateBuffers(u32_t latest, u32_t num, ObjectUid_t *uids);
  void STD_GenerateBuffers(u32_t latest, u32_t num, ObjectUid_t *uids);
  void ARB_GenerateBuffers(u32_t latest, u32_t num, ObjectUid_t *uids);

  // clang-format off
  DECL_GENERIC_CALLBACK_FUNC(void, OGLGenericBufferHelper, deleteBuffers, u32_t, ObjectUid_t *)
  MTHD_VIRTUAL(void deleteBuffers(u32_t num, ObjectUid_t *uids) { 
     (this->*deleteBuffers_)(num, uids); 
  });
  // clang-format on

  void EMU_DeleteBuffers(u32_t num, ObjectUid_t *uids);
  void STD_DeleteBuffers(u32_t num, ObjectUid_t *uids);
  void ARB_DeleteBuffers(u32_t num, ObjectUid_t *uids);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bindBuffer, BufferTarget, ObjectUidOpt_t)
  void EMU_BindBuffer(BufferTarget target, ObjectUidOpt_t uid);
  void STD_BindBuffer(BufferTarget target, ObjectUidOpt_t uid);
  void ARB_BindBuffer(BufferTarget target, ObjectUidOpt_t uid);

  DECLARE_GENERIC_MEMBER(
      void, OGLGenericBufferHelper, bindBufferRange, BufferTarget, ObjectUidOpt_t, u32_t, ptrdiff_t, ptrdiff_t)
  void STD_BindBufferRange(BufferTarget target, ObjectUidOpt_t uid, u32_t buf, ptrdiff_t offset, ptrdiff_t size);
  void EXT_BindBufferRange(BufferTarget target, ObjectUidOpt_t uid, u32_t buf, ptrdiff_t offset, ptrdiff_t size);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bufferData, BufferTarget, ptrdiff_t, const void *, u32_t)
  void EMU_BufferData(BufferTarget target, ptrdiff_t size, const void *data, u32_t usage);
  void STD_BufferData(BufferTarget target, ptrdiff_t size, const void *data, u32_t usage);
  void ARB_BufferData(BufferTarget target, ptrdiff_t size, const void *data, u32_t usage);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, bufferSubData, BufferTarget, ptrdiff_t, ptrdiff_t, const void *)
  void EMU_BufferSubData(BufferTarget target, ptrdiff_t offset, ptrdiff_t size, const void *data);
  void STD_BufferSubData(BufferTarget target, ptrdiff_t offset, ptrdiff_t size, const void *data);
  void ARB_BufferSubData(BufferTarget target, ptrdiff_t offset, ptrdiff_t size, const void *data);

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, flush, BufferTarget, ptrdiff_t, ptrdiff_t)
  void STD_FlushMappedBufferRange(BufferTarget target, ptrdiff_t offset, ptrdiff_t len);

  DECLARE_GENERIC_MEMBER(void *, OGLGenericBufferHelper, mapBuffer, BufferTarget, u32_t)
  auto EMU_MapBuffer(BufferTarget target, u32_t access) -> void *;
  auto STD_MapBuffer(BufferTarget target, u32_t access) -> void *;
  auto ARB_MapBuffer(BufferTarget target, u32_t access) -> void *;
  auto OES_MapBuffer(BufferTarget target, u32_t access) -> void *;

  DECLARE_GENERIC_MEMBER(void *, OGLGenericBufferHelper, mapBufferRange, BufferTarget, i32_t, i32_t, u32_t)
  auto EMU_MapBufferRange(BufferTarget target, i32_t offset, i32_t len, u32_t access) -> void *;
  auto STD_MapBufferRange(BufferTarget target, i32_t offset, i32_t len, u32_t access) -> void *;
  auto EXT_MapBufferRange(BufferTarget target, i32_t offset, i32_t len, u32_t access) -> void *;

  DECLARE_GENERIC_MEMBER(u8_t, OGLGenericBufferHelper, unmapBuffer, BufferTarget)
  auto EMU_UnmapBuffer(BufferTarget target) -> u8_t;
  auto STD_UnmapBuffer(BufferTarget target) -> u8_t;
  auto ARB_UnmapBuffer(BufferTarget target) -> u8_t;
  auto OES_UnmapBuffer(BufferTarget target) -> u8_t;

  DECLARE_GENERIC_MEMBER(u8_t, OGLGenericBufferHelper, isBuffer, ObjectUidOpt_t)
  auto EMU_IsBuffer(ObjectUidOpt_t uid) -> u8_t;
  auto STD_IsBuffer(ObjectUidOpt_t uid) -> u8_t;
  auto ARB_IsBuffer(ObjectUidOpt_t uid) -> u8_t;

  DECLARE_GENERIC_MEMBER(void, OGLGenericBufferHelper, getBufferParam, BufferTarget, u32_t, i32_t *)
  void EMU_GetBufferParam(BufferTarget target, u32_t pname, i32_t *params);
  void STD_GetBufferParam(BufferTarget target, u32_t pname, i32_t *params);
  void ARB_GetBufferParam(BufferTarget target, u32_t pname, i32_t *params);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLGENERICBUFFERHELPER_HPP
