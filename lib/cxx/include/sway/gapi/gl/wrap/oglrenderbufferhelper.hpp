#ifndef SWAY_GAPI_GL_WRAP_OGLRENDERBUFFERHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLRENDERBUFFERHELPER_HPP

#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>
#include <sway/math.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLRenderBufferHelper {
public:
  OGLRenderBufferHelper();

  DECLARE_GENERIC_MEMBER(std::vector<u32_t>, OGLRenderBufferHelper, generateRenderBuffers, i32_t)
  auto EMU_GenerateRenderBuffers(i32_t num) -> std::vector<u32_t>;
  auto STD_GenerateRenderBuffers(i32_t num) -> std::vector<u32_t>;
  auto EXT_GenerateRenderBuffers(i32_t num) -> std::vector<u32_t>;

  DECLARE_GENERIC_MEMBER(void, OGLRenderBufferHelper, deleteRenderBuffers, i32_t, const u32_t *)
  void EMU_DeleteRenderBuffers(i32_t num, const u32_t *bufs);
  void STD_DeleteRenderBuffers(i32_t num, const u32_t *bufs);
  void EXT_DeleteRenderBuffers(i32_t num, const u32_t *bufs);

  DECLARE_GENERIC_MEMBER(void, OGLRenderBufferHelper, bindRenderBuffer, u32_t, std::optional<u32_t>)
  void EMU_BindRenderBuffer(u32_t target, std::optional<u32_t> buf);
  void STD_BindRenderBuffer(u32_t target, std::optional<u32_t> buf);
  void EXT_BindRenderBuffer(u32_t target, std::optional<u32_t> buf);

  DECLARE_GENERIC_MEMBER(bool, OGLRenderBufferHelper, isRenderBuffer, std::optional<u32_t>)
  auto EMU_IsRenderBuffer(std::optional<u32_t> buf) -> bool;
  auto STD_IsRenderBuffer(std::optional<u32_t> buf) -> bool;
  auto EXT_IsRenderBuffer(std::optional<u32_t> buf) -> bool;

  DECLARE_GENERIC_MEMBER(
      void, OGLRenderBufferHelper, setRenderBufferStorage, u32_t, PixelFormat, const math::size2i_t &)
  void EMU_SetRenderBufferStorage(u32_t target, PixelFormat fmt, const math::size2i_t &size);
  void STD_SetRenderBufferStorage(u32_t target, PixelFormat fmt, const math::size2i_t &size);
  void EXT_SetRenderBufferStorage(u32_t target, PixelFormat fmt, const math::size2i_t &size);

  DECLARE_GENERIC_MEMBER(
      void, OGLRenderBufferHelper, setRenderBufferStorageMultisample, u32_t, i32_t, PixelFormat, const math::size2i_t &)
  void EMU_SetRenderBufferStorageMultisample(u32_t target, i32_t samples, PixelFormat fmt, const math::size2i_t &size);
  void STD_SetRenderBufferStorageMultisample(u32_t target, i32_t samples, PixelFormat fmt, const math::size2i_t &size);
  void EXT_SetRenderBufferStorageMultisample(u32_t target, i32_t samples, PixelFormat fmt, const math::size2i_t &size);

  DECLARE_GENERIC_MEMBER(
      void, OGLRenderBufferHelper, blitFrameBuffer, const math::rect4i_t &, const math::rect4i_t &, u32_t, u32_t)
  void EMU_BlitFrameBuffer(const math::rect4i_t &src, const math::rect4i_t &dst, u32_t mask, u32_t filter);
  void STD_BlitFrameBuffer(const math::rect4i_t &src, const math::rect4i_t &dst, u32_t mask, u32_t filter);
  void EXT_BlitFrameBuffer(const math::rect4i_t &src, const math::rect4i_t &dst, u32_t mask, u32_t filter);

  DECLARE_GENERIC_MEMBER(void, OGLRenderBufferHelper, getRenderBufferParameter, u32_t, u32_t, i32_t *)
  void EMU_GetRenderBufferParameter(u32_t target, u32_t pname, i32_t *params);
  void STD_GetRenderBufferParameter(u32_t target, u32_t pname, i32_t *params);
  void EXT_GetRenderBufferParameter(u32_t target, u32_t pname, i32_t *params);
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_WRAP_OGLRENDERBUFFERHELPER_HPP
