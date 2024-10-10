#ifndef SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFERHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFERHELPER_HPP

#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLFrameBufferHelperIface {
public:
  DTOR_VIRTUAL_DEFAULT(OGLFrameBufferHelperIface);

  PURE_VIRTUAL(void generateFramebuffers(u32_t latest, i32_t num, u32_t *uids));

  PURE_VIRTUAL(void deleteFramebuffers(i32_t num, u32_t *uids));
};

class OGLFrameBufferHelper : public OGLFrameBufferHelperIface {
public:
  OGLFrameBufferHelper();

  DTOR_VIRTUAL_DEFAULT(OGLFrameBufferHelper);

  // clang-format off
  DECL_GENERIC_CALLBACK_FUNC(void, OGLFrameBufferHelper, generateFramebuffers, u32_t, i32_t, ObjectUid_t *)
  MTHD_VIRTUAL(void generateFramebuffers(u32_t latest, i32_t num, ObjectUid_t *uids) { 
     (this->*generateFramebuffers_)(latest, num, uids); 
  });
  // clang-format on

  void EMU_GenerateFramebuffers(u32_t latest, i32_t num, ObjectUid_t *uids);
  void STD_GenerateFramebuffers(u32_t latest, i32_t num, ObjectUid_t *uids);
  void EXT_GenerateFramebuffers(u32_t latest, i32_t num, ObjectUid_t *uids);

  // clang-format off
  DECL_GENERIC_CALLBACK_FUNC(void, OGLFrameBufferHelper, deleteFramebuffers, i32_t,const ObjectUid_t *)
  MTHD_VIRTUAL(void deleteFramebuffers(i32_t num, ObjectUid_t *uids) { 
     (this->*deleteFramebuffers_)(num, uids); 
  });
  // clang-format on

  void EMU_DeleteFramebuffers(i32_t num, const ObjectUid_t *uids);
  void STD_DeleteFramebuffers(i32_t num, const ObjectUid_t *uids);
  void EXT_DeleteFramebuffers(i32_t num, const ObjectUid_t *uids);

  DECLARE_GENERIC_MEMBER(void, OGLFrameBufferHelper, bindFramebuffer, u32_t, std::optional<u32_t>)
  void EMU_BindFramebuffer(u32_t target, std::optional<u32_t> framebuffer);
  void STD_BindFramebuffer(u32_t target, std::optional<u32_t> framebuffer);
  void EXT_BindFramebuffer(u32_t target, std::optional<u32_t> framebuffer);

  DECLARE_GENERIC_MEMBER(bool, OGLFrameBufferHelper, isFramebuffer, u32_t)
  auto EMU_IsFramebuffer(u32_t framebuffer) -> bool;
  auto STD_IsFramebuffer(u32_t framebuffer) -> bool;
  auto EXT_IsFramebuffer(u32_t framebuffer) -> bool;

  DECLARE_GENERIC_MEMBER(
      void, OGLFrameBufferHelper, framebufferTexture2D, u32_t, u32_t, u32_t, std::optional<u32_t>, i32_t)
  void EMU_FramebufferTexture2D(
      u32_t target, u32_t attachment, u32_t textarget, std::optional<u32_t> texture, i32_t level);
  void STD_FramebufferTexture2D(
      u32_t target, u32_t attachment, u32_t textarget, std::optional<u32_t> texture, i32_t level);
  void EXT_FramebufferTexture2D(
      u32_t target, u32_t attachment, u32_t textarget, std::optional<u32_t> texture, i32_t level);

  DECLARE_GENERIC_MEMBER(void, OGLFrameBufferHelper, framebufferRenderbuffer, u32_t, u32_t, u32_t, std::optional<u32_t>)
  void EMU_FramebufferRenderbuffer(
      u32_t target, u32_t attachment, u32_t renderbuffertarget, std::optional<u32_t> renderbuffer);
  void STD_FramebufferRenderbuffer(
      u32_t target, u32_t attachment, u32_t renderbuffertarget, std::optional<u32_t> renderbuffer);
  void EXT_FramebufferRenderbuffer(
      u32_t target, u32_t attachment, u32_t renderbuffertarget, std::optional<u32_t> renderbuffer);

  DECLARE_GENERIC_MEMBER(u32_t, OGLFrameBufferHelper, checkFramebufferStatus, u32_t)
  auto EMU_CheckFramebufferStatus(u32_t target) -> u32_t;
  auto STD_CheckFramebufferStatus(u32_t target) -> u32_t;
  auto EXT_CheckFramebufferStatus(u32_t target) -> u32_t;

  DECLARE_GENERIC_MEMBER(void, OGLFrameBufferHelper, getFramebufferAttachmentParamI, u32_t, u32_t, u32_t, i32_t *)
  void EMU_GetFramebufferAttachmentParamI(u32_t target, u32_t attachment, u32_t pname, i32_t *params);
  void STD_GetFramebufferAttachmentParamI(u32_t target, u32_t attachment, u32_t pname, i32_t *params);
  void EXT_GetFramebufferAttachmentParamI(u32_t target, u32_t attachment, u32_t pname, i32_t *params);
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_WRAP_OGLFRAMEBUFFERHELPER_HPP
