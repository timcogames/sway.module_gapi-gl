#ifndef SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFERHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFERHELPER_HPP

#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLFramebufferHelper {
public:
  OGLFramebufferHelper();

  DECLARE_GENERIC_MEMBER(void, OGLFramebufferHelper, generateFramebuffers, i32_t, u32_t *)
  void EMU_GenerateFramebuffers(i32_t num, u32_t *framebuffers);
  void STD_GenerateFramebuffers(i32_t num, u32_t *framebuffers);
  void EXT_GenerateFramebuffers(i32_t num, u32_t *framebuffers);

  DECLARE_GENERIC_MEMBER(void, OGLFramebufferHelper, deleteFramebuffers, i32_t, const u32_t *)
  void EMU_DeleteFramebuffers(i32_t num, const u32_t *framebuffers);
  void STD_DeleteFramebuffers(i32_t num, const u32_t *framebuffers);
  void EXT_DeleteFramebuffers(i32_t num, const u32_t *framebuffers);

  DECLARE_GENERIC_MEMBER(void, OGLFramebufferHelper, bindFramebuffer, u32_t, std::optional<u32_t>)
  void EMU_BindFramebuffer(u32_t target, std::optional<u32_t> framebuffer);
  void STD_BindFramebuffer(u32_t target, std::optional<u32_t> framebuffer);
  void EXT_BindFramebuffer(u32_t target, std::optional<u32_t> framebuffer);

  DECLARE_GENERIC_MEMBER(bool, OGLFramebufferHelper, isFramebuffer, u32_t)
  auto EMU_IsFramebuffer(u32_t framebuffer) -> bool;
  auto STD_IsFramebuffer(u32_t framebuffer) -> bool;
  auto EXT_IsFramebuffer(u32_t framebuffer) -> bool;

  DECLARE_GENERIC_MEMBER(
      void, OGLFramebufferHelper, framebufferTexture2D, u32_t, u32_t, u32_t, std::optional<u32_t>, i32_t)
  void EMU_FramebufferTexture2D(
      u32_t target, u32_t attachment, u32_t textarget, std::optional<u32_t> texture, i32_t level);
  void STD_FramebufferTexture2D(
      u32_t target, u32_t attachment, u32_t textarget, std::optional<u32_t> texture, i32_t level);
  void EXT_FramebufferTexture2D(
      u32_t target, u32_t attachment, u32_t textarget, std::optional<u32_t> texture, i32_t level);

  DECLARE_GENERIC_MEMBER(void, OGLFramebufferHelper, framebufferRenderbuffer, u32_t, u32_t, u32_t, std::optional<u32_t>)
  void EMU_FramebufferRenderbuffer(
      u32_t target, u32_t attachment, u32_t renderbuffertarget, std::optional<u32_t> renderbuffer);
  void STD_FramebufferRenderbuffer(
      u32_t target, u32_t attachment, u32_t renderbuffertarget, std::optional<u32_t> renderbuffer);
  void EXT_FramebufferRenderbuffer(
      u32_t target, u32_t attachment, u32_t renderbuffertarget, std::optional<u32_t> renderbuffer);

  DECLARE_GENERIC_MEMBER(u32_t, OGLFramebufferHelper, checkFramebufferStatus, u32_t)
  auto EMU_CheckFramebufferStatus(u32_t target) -> u32_t;
  auto STD_CheckFramebufferStatus(u32_t target) -> u32_t;
  auto EXT_CheckFramebufferStatus(u32_t target) -> u32_t;

  DECLARE_GENERIC_MEMBER(void, OGLFramebufferHelper, getFramebufferAttachmentParamI, u32_t, u32_t, u32_t, i32_t *)
  void EMU_GetFramebufferAttachmentParamI(u32_t target, u32_t attachment, u32_t pname, i32_t *params);
  void STD_GetFramebufferAttachmentParamI(u32_t target, u32_t attachment, u32_t pname, i32_t *params);
  void EXT_GetFramebufferAttachmentParamI(u32_t target, u32_t attachment, u32_t pname, i32_t *params);
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFERHELPER_HPP
