#ifndef SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTHELPER_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLVertexAttribLayoutHelper {
public:
  OGLVertexAttribLayoutHelper();

  DECLARE_GENERIC_MEMBER(OGLVertexAttribLayoutHelper, EnableArray, void, u32_t)
  void EMU_EnableVertexAttribArray(u32_t index);
  void STD_EnableVertexAttribArray(u32_t index);
  void ARB_EnableVertexAttribArray(u32_t index);

  DECLARE_GENERIC_MEMBER(OGLVertexAttribLayoutHelper, DisableArray, void, u32_t)
  void EMU_DisableVertexAttribArray(u32_t index);
  void STD_DisableVertexAttribArray(u32_t index);
  void ARB_DisableVertexAttribArray(u32_t index);

  DECLARE_GENERIC_MEMBER(OGLVertexAttribLayoutHelper, Setup, void, u32_t, s32_t, u32_t, u8_t, s32_t, const void *)
  void EMU_SetupVertexAttribPointer(
      u32_t index, s32_t size, u32_t type, u8_t normalized, s32_t stride, const void *pointer);
  void STD_SetupVertexAttribPointer(
      u32_t index, s32_t size, u32_t type, u8_t normalized, s32_t stride, const void *pointer);
  void ARB_SetupVertexAttribPointer(
      u32_t index, s32_t size, u32_t type, u8_t normalized, s32_t stride, const void *pointer);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTHELPER_HPP
