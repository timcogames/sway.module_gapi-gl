#ifndef SWAY_GAPI_GL_WRAP_OGLINFOHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLINFOHELPER_HPP

#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLInfoHelper {
public:
  OGLInfoHelper();

  DECLARE_GENERIC_MEMBER(void, OGLInfoHelper, getObjectParameter, u32_t, u32_t, s32_t *)
  void EMU_GetObjectParameter(u32_t obj, u32_t pname, s32_t *params);
  void STD_GetObjectParameter(u32_t obj, u32_t pname, s32_t *params);
  void ARB_GetObjectParameter(u32_t obj, u32_t pname, s32_t *params);

  DECLARE_GENERIC_MEMBER(void, OGLInfoHelper, getInfoLog, u32_t, s32_t, s32_t *, lpstr_t)
  void EMU_GetInfoLog(u32_t obj, s32_t maxLength, s32_t *length, lpstr_t infoLog);
  void STD_GetInfoLog(u32_t obj, s32_t maxLength, s32_t *length, lpstr_t infoLog);
  void ARB_GetInfoLog(u32_t obj, s32_t maxLength, s32_t *length, lpstr_t infoLog);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLINFOHELPER_HPP
