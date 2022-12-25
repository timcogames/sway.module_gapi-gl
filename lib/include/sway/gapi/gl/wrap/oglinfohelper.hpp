#ifndef SWAY_GAPI_GL_WRAP_OGLINFOHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLINFOHELPER_HPP

#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLInfoHelper {
public:
  OGLInfoHelper();

  DECLARE_GENERIC_MEMBER(OGLInfoHelper, getObjectParameter, void, u32_t, u32_t, s32_t *)
  auto EMU_getObjectParameter(u32_t obj, u32_t pname, s32_t *params) -> void;
  auto STD_getObjectParameter(u32_t obj, u32_t pname, s32_t *params) -> void;
  auto ARB_getObjectParameter(u32_t obj, u32_t pname, s32_t *params) -> void;

  DECLARE_GENERIC_MEMBER(OGLInfoHelper, getInfoLog, void, u32_t, s32_t, s32_t *, lpstr_t)
  auto EMU_getInfoLog(u32_t obj, s32_t maxLength, s32_t *length, lpstr_t infoLog) -> void;
  auto STD_getInfoLog(u32_t obj, s32_t maxLength, s32_t *length, lpstr_t infoLog) -> void;
  auto ARB_getInfoLog(u32_t obj, s32_t maxLength, s32_t *length, lpstr_t infoLog) -> void;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLINFOHELPER_HPP
