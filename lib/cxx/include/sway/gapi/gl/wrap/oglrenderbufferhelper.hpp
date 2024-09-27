#ifndef SWAY_GAPI_GL_WRAP_OGLRENDERBUFFERHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLRENDERBUFFERHELPER_HPP

#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>
#include <sway/math.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLRenderBufferHelper {
public:
  OGLRenderBufferHelper();

  DECLARE_GENERIC_MEMBER(std::vector<u32_t>, OGLRenderBufferHelper, generateRenderBuffers, i32_t)
  auto EMU_GenerateRenderBuffers(i32_t num);
  auto STD_GenerateRenderBuffers(i32_t num);
  auto EXT_GenerateRenderBuffers(i32_t num);

  DECLARE_GENERIC_MEMBER(void, OGLRenderBufferHelper, deleteRenderBuffers, i32_t, const u32_t *)
  void EMU_DeleteRenderBuffers(i32_t num, const u32_t *bufs);
  void STD_DeleteRenderBuffers(i32_t num, const u32_t *bufs);
  void EXT_DeleteRenderBuffers(i32_t num, const u32_t *bufs);

  DECLARE_GENERIC_MEMBER(void, OGLRenderBufferHelper, bindRenderBuffer, u32_t, std::optional<u32_t>)
  void EMU_BindRenderBuffer(u32_t target, std::optional<u32_t> buf);
  void STD_BindRenderBuffer(u32_t target, std::optional<u32_t> buf);
  void EXT_BindRenderBuffer(u32_t target, std::optional<u32_t> buf);

  DECLARE_GENERIC_MEMBER(bool, OGLRenderBufferHelper, isRenderBuffer, u32_t)
  auto EMU_IsRenderBuffer(u32_t buf) -> bool;
  auto STD_IsRenderBuffer(u32_t buf) -> bool;
  auto EXT_IsRenderBuffer(u32_t buf) -> bool;

  DECLARE_GENERIC_MEMBER(void, OGLRenderBufferHelper, setRenderBufferStorage, u32_t, u32_t, const math::size2i_t &)
  void EMU_SetRenderBufferStorage(u32_t target, u32_t frmt, const math::size2i_t &size) -> u32_t;
  void STD_SetRenderBufferStorage(u32_t target, u32_t frmt, const math::size2i_t &size) -> u32_t;
  void EXT_SetRenderBufferStorage(u32_t target, u32_t frmt, const math::size2i_t &size) -> u32_t;

  DECLARE_GENERIC_MEMBER(void, OGLRenderBufferHelper, getRenderBufferParameter, u32_t, u32_t, i32_t *)
  void EMU_GetRenderBufferParameter(u32_t target, u32_t pname, i32_t *params);
  void STD_GetRenderBufferParameter(u32_t target, u32_t pname, i32_t *params);
  void EXT_GetRenderBufferParameter(u32_t target, u32_t pname, i32_t *params);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLRENDERBUFFERHELPER_HPP
